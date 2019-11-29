package fr.samuel.osu_extractor;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.Collectors;

public class DirectoryFileComparator {
	private File InputDirectory =null;
	private File OutputDirectory = null;
	
	private ArrayList<File> InputFileList = null;
	private ArrayList<File> OutputFileList = null;
	private ArrayList<File> fileToCopyInOutputDirectory = null;
	private ArrayList<String> outputDirectoryFilesNames = null;
	
	private String _extend = null, _pathInputDirectory = null, _PathOutputDirectory = null;
	
	public DirectoryFileComparator(String extend, String pathInputDirectory, String PathOutputDirectory) {
		_extend = extend;
		_pathInputDirectory = pathInputDirectory;
		_PathOutputDirectory = PathOutputDirectory;
	}
	
	public void process() {
		InputDirectory =new File(_pathInputDirectory);
		OutputDirectory = new File(_PathOutputDirectory);
		double timer = System.currentTimeMillis();
		//extract all file.extend file from input directory
		InputFileList = getFilesWithExtension(InputDirectory, _extend);
		
		//extract all file.extend file from output directory
		OutputFileList = getFilesWithExtension(OutputDirectory, _extend);
		System.out.println("reading file done in : "+(System.currentTimeMillis()-timer));
		timer =System.currentTimeMillis();
		
		
		/**
		 * 				EXTRACT OUTPUT DIRECTORY FILES NAMES
		 */
		outputDirectoryFilesNames = extract_outputDirectory_filesNames(_extend);
		
		
		//outputDirectoryFilesNames.forEach(System.out::println); //test 
		
		/**
		 * 				SELECT WHAT FILES WE WANT TO COPY THAT WE DON'T HAVE ALREADY IN THE DIRECTORY
		 */
		//the collection of file we need to copy
		fileToCopyInOutputDirectory = getFileToCopyInOutputDirectory();
		//fileToCopyInOutputDirectory.forEach(System.out::println);	//test
		
		System.out.println("processing data done in : "+(System.currentTimeMillis()-timer));
		timer = System.currentTimeMillis();
		/**
		 * 					COPY THE FILE AND MANAGING THE DOUBLE BY INSERTING AN INDICE AT THE END OF THE DOUBLE FILE NAME
		 */
		copyNewFiles(_PathOutputDirectory);
		
		System.out.println("copying new file done in : "+(System.currentTimeMillis()-timer));
	}
	/**
	 * @return the name of the output directory files without the extension in outputFilesNames
	 */
	private ArrayList<String> extract_outputDirectory_filesNames(String extension) {
		return new ArrayList<String>(
				OutputFileList.stream()
				//get the file name and delete the .mp3 extension
				.map(file -> file.getName().substring(0, file.getName().length()-extension.length()))
				.collect(Collectors.toList()));
	}
	
	/**
	 * get mp3 file in directory and sub directory
	 * @param directory the target directory
	 */
	private ArrayList<File> getFilesWithExtension(File directory, String extend) {
		ArrayList<File> result = new ArrayList<File>(
				//get stream from osu song directory content ( the content are only sub directory)
				Arrays.stream(directory.listFiles())
				//here we extract file from the sub directory indiscriminately and we have a stream of File[]	"?" if its a directory extract files in else just create an array with one element to handle errors
				.map(file -> file.isDirectory() ? file.listFiles() : new File[] {file})
				//here we merge ours File arrays into one 
				.flatMap(Arrays::stream)
				//here we filter all the file and and only keep the one who end with ".mp3"
				.filter(file -> file.getName().toLowerCase().endsWith(".mp3"))
				//here we collect our stream result into an ArrayList
				.collect(Collectors.toList()));
		return result;
	}
	
	/**
	 * copy all the new files detected in the input directory to the output directory and place  them in a sub directory 
	 * 
	 * @param PathOutputDirectory the output where new file will be copied
	 */
	private void copyNewFiles(String PathOutputDirectory) {
		//create a new directory for all the new songs
		String OutputDirectory_subDirectory_name = LocalDate.now().format(DateTimeFormatter.ISO_LOCAL_DATE);
		//System.out.println(OutputDirectory_subDirectory_name);		//test
		File OutputDirectory_subDirectory = new File(PathOutputDirectory+"\\"+OutputDirectory_subDirectory_name);
		if(!OutputDirectory_subDirectory.exists())
			OutputDirectory_subDirectory.mkdir();
		OutputDirectory_subDirectory = null;
		
		//start the copy
		for(File f : fileToCopyInOutputDirectory) {
			Path fileToCopy = f.toPath(), futurFilePath = null;
			//the actual index if 0 then it will not appear
			int n = 0;
					
			//the condition to end the loot that say we have found an available index
			boolean fileHasBeenCopied = false;
					
			//the part of the file name that don't change 
			/**
			 * for example 
			 * D:/MyDirectory/Songs/HanaHana/audio.mp3
			 * then the output file name is :
			 * HanaHana.mp3
			 * and if there are more audio in the directory then
			 * D:/MyDirectory/Songs/HanaHana/effects.mp3
			 * it will be copied as :
			 * HanaHana 1.mp3
			 */
			String futurFileGenericName = PathOutputDirectory+"\\"+OutputDirectory_subDirectory_name+"\\"+f.getAbsolutePath().split("\\\\")[f.getAbsolutePath().split("\\\\").length-2];
			while(!fileHasBeenCopied) {
				File futurFile = null;
				//if we haven't changed the file name yet (n=0)
				if(n == 0)
					futurFile = new File(futurFileGenericName+".mp3");
				else
					futurFile = new File(futurFileGenericName+" "+n+".mp3");
				//if the file we want to create already exist that mean the index isn't available
				if(futurFile.exists()) {
					n ++;
				}
						//else copy the file in the output directory
				else {
					futurFilePath = futurFile.toPath();
					try {
					  Files.copy(fileToCopy, futurFilePath, StandardCopyOption.COPY_ATTRIBUTES);
					  //System.out.println("copying file to "+futurFile.getAbsolutePath());		//test
					} catch (IOException e) { 
						//e.printStackTrace();	
						}
					finally {
						//we break the loop
						fileHasBeenCopied = true;
					}
				}
			}
		}
	}
	
	private ArrayList<File> getFileToCopyInOutputDirectory(){
		return new ArrayList<File>(InputFileList.stream()
				.filter(
						file -> !outputDirectoryFilesNames
						//if the file name we have already in output directory are contained in file we scanned from the input directory then don't copy it
						.contains(file
								//we get the file absolute path and cut the file name because the output file name ae the same as the parent directory of the input file
								.getAbsolutePath().split("\\\\")[
								               //can't do inoother way because can't init var in stream
								               file.getAbsolutePath().split("\\\\").length-2]))
				.collect(Collectors.toList()) );
	}
}
