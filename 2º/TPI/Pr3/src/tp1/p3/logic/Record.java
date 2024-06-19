package tp1.p3.logic;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

import tp1.p3.control.Level;


public class Record {;
	public static int score;
	public int [] score_vector = {0,0,0};
	public static final String[] levels = {"EASY","HARD","INSANE"};
	public Record() {
		score = 0;
	}
	public int getScore() {
		return score;
	}
	public void loadScore() {
		try (FileReader fr = new FileReader("record.txt")) {
			String line = "";
			int n = fr.read();	
			while (fr.read() != -1) {
				line += (char)n;
				if (line.equals("EASY : ")) {
					
				}
			}
		} catch (FileNotFoundException e) {
			System.out.println(e.getMessage());
		} catch (IOException e) {
			System.out.println(e.getMessage());
		} 
	}
	public void saveScore(Level level) {
		boolean i = false;
		File file = new File("record.txt");
		try (BufferedWriter bw = new BufferedWriter(new FileWriter(file, true));) {
			Scanner scanner = new Scanner(file);
			String level_aux = String.valueOf(level);
			while(scanner.hasNext()) {
				String level_string = scanner.next();
				if(level_string.equals(level_aux)) {
					i = true;
					String dospuntos = scanner.next();
					int score_aux =  scanner.nextInt();
					if(score_aux < score) {
						System.out.println("New record!");
						score_vector[level.ordinal()] = score;
//						if(level_string.equals("EASY")) {
//							score_vector[0] = score;
//						}else if(level_string.equals("HARD")) {
//							score_vector[1] = score;
//						}else if(level_string.equals("INSANE")) {
//							score_vector[2] = score;
//						}
//						BufferedWriter bw1 = new BufferedWriter(new FileWriter("record.txt"));
//						bw1.write("");
//						bw1.close();
						bw.write(levels[level.ordinal()] + " : " + score_vector[level.ordinal()] + "\r\n");
//					for(int x = 0; x < score_vector.length;x++) {
//						bw.write(levels[x] + " : " + score_vector[x] + "\r\n");
//					}
					}
				}
			}
			if(!i) {
//				BufferedWriter bw1 = new BufferedWriter(new FileWriter("record.txt"));
//				bw1.write("");
//				bw1.close();
//				BufferedWriter bw = new BufferedWriter(new FileWriter("record.txt",true));
				System.out.println("New record!");
				score_vector[level.ordinal()] = score;
				for(int x = 0; x < score_vector.length;x++) {
					bw.write(levels[x] + " : " + score_vector[x] + "\r\n");

				}
			}
		} catch(IOException e) {
			System.out.println(e.getMessage());
		}
	}
}