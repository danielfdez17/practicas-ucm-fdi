package tp1.p1.logic;

import java.util.Random;

import tp1.p1.control.Level;
import tp1.p1.logic.gameobjects.PeashooterList;
import tp1.p1.logic.gameobjects.SunflowerList;
import tp1.p1.logic.gameobjects.Zombie;
import tp1.p1.logic.gameobjects.ZombieList;

/**
 * Manage zombies in the game.
 *
 */
public class ZombiesManager {
	
	// ATRIBUTES
	private Game game;
	private Level level;
	private Random rand;
	private static int remainingZombies;
	private static int zombiesAppearences;

	public ZombiesManager(Game game, Level level, Random rand) {
		this.game = game;
		this.level = level;
		this.rand = rand;
		remainingZombies = level.getNumberOfZombies();
		zombiesAppearences = 0;
	}

	/**
	 * Checks if the game should add (if possible) a zombie to the game.
	 * 
	 * @return <code>true</code> if a zombie should be added to the game.
	 */
	private boolean shouldAddZombie() {
		return rand.nextDouble() < level.getZombieFrequency();
	}
	/**
	 * Return a random row within the board limits.
	 * 
	 * @return a random row.
	 */
	private int randomZombieRow() {
		return rand.nextInt(Game.NUM_ROWS);
	}
	
	public boolean addZombie() {
		int row = randomZombieRow();
		return addZombie(row);
	}

	public boolean addZombie(int row) {
		boolean canAdd = getRemainingZombies() > 0 && shouldAddZombie() && isPositionEmpty(Game.NUM_COLS, row);
		if(canAdd) {
			Zombie zombie = new Zombie(this.game);
			zombie.setCol(Game.NUM_COLS);
			zombie.setRow(row);
			ZombieList.addZombie(zombie);
			zombiesAppearences++;
		}
		return canAdd;
	}
	// Returns true if the position numCols,row is empty. Retunrs false in other cases
	private boolean isPositionEmpty(int numCols, int row) {
		boolean found = false;
		found = SunflowerList.searchSunflower(numCols, row);
		if (!found) {
			found = PeashooterList.searchPeashooter(numCols, row);
			if(!found) {
				found = ZombieList.searchZombie(numCols, row);
			}
		}
		return !found;
	}
	// Returns the zombies that did not appear in the game
	public static int getRemainingZombies() {
		return (remainingZombies - zombiesAppearences);
	}
	// Updates the zombies appearences
	public static void UpdateZombiesAppearences() {
		zombiesAppearences++;
	}
}