package fr.samuel.osu_extractor.test;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class SpeedTest {
	public SpeedTest(String osuPath){
		File f = new File(osuPath);
		
		// test 1
		long time= System.currentTimeMillis(), t2 = 0;
		
		ArrayList<File> filel = new ArrayList<File>();
		listf(osuPath, filel);
		time = (System.currentTimeMillis()-time);
		filel.stream().forEach(System.out::println);
		
		
		// test 2
		t2 = time;
		time = System.currentTimeMillis();
		ArrayList<File> res = new ArrayList<File>( Arrays.asList(f.listFiles()));
		filel = (ArrayList<File>) res.stream().filter(File::isFile).collect(Collectors.toList());
		time = System.currentTimeMillis()-time;
		filel.stream().forEach(System.out::println);
		
		System.out.println("system 1 : "+t2+"\nsystem 2 :"+time);
		/*
		 * Result :
		 * 	System 1 (for): 2303 ms 
		 *  System 2 (Stream): 47 ms
		 */
	}
	
	public static void listf(String directoryName, List<File> files) {
	    File directory = new File(directoryName);

	    // Get all files from a directory.
	    File[] fList = directory.listFiles();
	    if(fList != null)
	        for (File file : fList) {      
	            if (file.isFile())
	                files.add(file);
	            else if (file.isDirectory()) 
	                listf(file.getAbsolutePath(), files);
	        }
	}
}
