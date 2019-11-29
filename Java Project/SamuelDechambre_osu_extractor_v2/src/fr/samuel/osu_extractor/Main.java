package fr.samuel.osu_extractor;

public class Main {	
	private static final String osuPath  = "D:/osu/Songs";
	private static final String outputPath  = "E:\\osu songs";
	//private static final String testInputString = "E:\\osu sample songs";
	
	public static void main(String[] args) {

		System.out.println("start");
		DirectoryFileComparator osu_resut_extraction_file_comparator = new DirectoryFileComparator(".mp3", osuPath, outputPath);
		osu_resut_extraction_file_comparator.process();
		System.out.println("end");
	}
}
