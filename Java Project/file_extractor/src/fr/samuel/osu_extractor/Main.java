package fr.samuel.osu_extractor;

public class Main {	
	private static final String osuSongsPath  = "C:\\Users\\samde\\Desktop\\Java\\PDF";
	private static final String outputPath  = "C:\\Users\\samde\\Desktop\\Java\\PDF out";
	//private static final String testInputString = "E:\\osu sample songs";
	
	public static void main(String[] args) {

		System.out.println("start");
		DirectoryFileComparator osu_resut_extraction_file_comparator = new DirectoryFileComparator(".pdf", osuSongsPath, outputPath);
		osu_resut_extraction_file_comparator.process();
		System.out.println("end");
	}
}
