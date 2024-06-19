package tp1.p1.control;

import static tp1.p1.view.Messages.*;

import java.util.Scanner;

import tp1.p1.logic.Game;
import tp1.p1.view.GamePrinter;
import tp1.p1.view.Messages;

/**
 * Accepts user input and coordinates the game execution logic.
 *
 */
public class Controller {

	private Game game;
	
	private Scanner scanner;

	private GamePrinter gamePrinter;

	public Controller(Game game, Scanner scanner) {
		this.game = game;
		this.scanner = scanner;
		this.gamePrinter = new GamePrinter(game);
	}
	/**
	 * Draw / Paint the game.
	 */
	private void printGame() {
		System.out.println(gamePrinter);
	}
	/**
	 * Prints the final message once the match is finished.
	 */
	public void printEndMessage() {
		System.out.println(gamePrinter.endMessage());
	}
	/**
	 * Show prompt and request command.
	 *
	 * @return the player command as words
	 */
	private String[] prompt() {
		System.out.print(Messages.PROMPT);
		String line = scanner.nextLine();
		String[] words = line.toLowerCase().trim().split("\\s+");
		System.out.println(debug(line));
		return words;
	}
	/**
	 * Runs the game logic.
	 */
	public void run() {
		int col, row;
		boolean printGame = true, exit = false, reset = false;
		while(!this.game.ended()) {
			exit = false;
			reset = false;
			if (printGame) {
				System.out.println(Messages.NUMBER_OF_CYCLES + " " + game.getCycles());
				System.out.println(Messages.NUMBER_OF_COINS + " " + game.getSuncoins());
				System.out.println(Messages.REMAINING_ZOMBIES + " " + game.getRemainingZombies());				
			}
			// 1. Draw
			if (printGame) {
				this.printGame();
			}
			// 2. User Action
			String[] words = new String[4];
			words = prompt();
			switch(words[0]) {
			case "add":
			case "a":
				printGame = true;
				if (words.length < 3) {
					System.out.println(Messages.ERROR.formatted(Messages.COMMAND_PARAMETERS_MISSING));	
					printGame = false;
				}
				else {
					col = Integer.parseInt(words[2]); // Converts string to integer
					row = Integer.parseInt(words[3]); // Converts string to integer
					this.game.addPlant(words[1], col, row);					
				}
			break;
			case "list":
			case "l":
				printGame = false;
				System.out.println(Messages.LIST);
				break;
			case "reset":
			case "r":
				reset = true;
				this.game.reset();
				break;
			case "help":
			case "h":
				printGame = false;
				System.out.println(Messages.HELP);
				break;
			case "exit":
			case "e":
				exit = true;
				this.game.exit();
				break;
			case "none":
			case "n":
			case "":
				printGame = true;
				break;
			default:
				System.out.println(Messages.ERROR.formatted(Messages.UNKNOWN_COMMAND));
				printGame = false;
				break;
			}
			if (printGame && !reset && !exit) {
				// 3. Game Action
				this.game.addZombie();				
				// 4. Update
				this.game.Update();				
			}
		}
		System.out.println(Messages.NUMBER_OF_CYCLES + " " + game.getCycles());
		System.out.println(Messages.NUMBER_OF_COINS + " " + game.getSuncoins());
		System.out.println(Messages.REMAINING_ZOMBIES + " " + game.getRemainingZombies());	
		this.printGame();
		System.out.println(Messages.GAME_OVER);
		if (game.zombiesArrival()) {
			System.out.println(Messages.ZOMBIES_WIN);
		}
		else if (game.playerWin()) {
			System.out.println(Messages.PLAYER_WINS);
		}
		else {
			System.out.println(Messages.PLAYER_QUITS);
		}
	}					
}