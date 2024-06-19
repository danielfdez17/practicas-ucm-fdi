package tp1.p3.control;

import static tp1.p3.view.Messages.debug;
import static tp1.p3.view.Messages.error;

import java.util.Scanner;

import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.Game;
import tp1.p3.view.GamePrinter;
import tp1.p3.view.Messages;

/**
 * Accepts user input and coordinates the game execution logic.
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
	// Prints the win message depending on the winner (zombies or the player)
	private void printWinner() {
		if (this.game.isFinished()) {
			if (this.game.playerWins()) {
				System.out.println(Messages.PLAYER_WINS);
			}
			else if (this.game.zombiesWin()) {
				System.out.println(Messages.ZOMBIES_WIN);
			}
		}
	}
	// Prints the exit message if user decides quit the game/match
	private void printExit() {
		if (this.game.isPlayerQuits()) {
			System.out.println(Messages.PLAYER_QUITS);
		}
	}
	/**
	 * Runs the game logic.
	 */
	public void run() {
		boolean refreshDisplay = true;

		while (!game.isFinished() && !game.isPlayerQuits()) {

			// 1. Draw
			if (refreshDisplay) {
				printGame();
			}

			String[] words = prompt();
				
			try {
				refreshDisplay = false;
				// 2-4. User action & Game Action & Update
				Command command = Command.parse(words);
				refreshDisplay = game.execute(command);
			} catch (GameException e) {
				System.out.println(error(e.getMessage()));
			}
		}
		printEndMessage();
		printWinner();
		printExit();
	}
}