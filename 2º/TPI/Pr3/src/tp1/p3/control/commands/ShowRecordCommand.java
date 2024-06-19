package tp1.p3.control.commands;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Scanner;

import tp1.p3.control.Command;
import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.GameWorld;
import tp1.p3.view.Messages;

public class ShowRecordCommand extends Command {

	@Override
	protected String getName() {
		return Messages.COMMAND_SHOW_RECORD_NAME;
	}

	@Override
	protected String getShortcut() {
		return Messages.COMMAND_SHOW_RECORD_SHORTCUT;
	}

	@Override
	public String getDetails() {
		return Messages.COMMAND_SHOW_RECORD_DETAILS;
	}

	@Override
	public String getHelp() {
		return Messages.COMMAND_SHOW_RECORD_HELP;
	}

	@Override
	public boolean execute(GameWorld game)throws GameException {
		// 1. Abrir el fichero "record.txt"
		// 2. Buscar el record del nivel actual
		// 3. Mostrarlo por pantalla
//		try {
//			File f = new File("record.txt");
//			Scanner scanner = new Scanner(f);
//			while(scanner.hasNext()) {
//				String level_string = scanner.next();
//				String level_aux = String.valueOf(this.level);
//				if(level_string.equals(level_aux)) {
//					String puntos = scanner.next();
//					int score_aux =  scanner.nextInt();
//					System.out.println(level_aux + " record is " + score_aux);
//					}
//				}
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//	}
		game.showRecord(); // debe devolver un boolean para indicar si se ha ejecutado o no el comando
		return false;
	}
}
