package tp1.p2.logic;

import java.util.Random;

import tp1.p2.control.Level;
import tp1.p2.logic.gameobjects.GameObject;
import tp1.p2.logic.gameobjects.Zombie;
import tp1.p2.logic.gameobjects.ZombieFactory;

/**
 * Manage zombies in the game.
 *
 */
public class ZombiesManager {

	// ATRIBUTES
	private GameWorld game;
	private Level level;
	private Random rand;
	private static int remainingZombies;
	private static int zombiesAlived;
	private static int zombiesAppearences;

	// BUILDER
	public ZombiesManager(GameWorld game, Level level, Random rand) {
		this.game = game;
		this.level = level;
		this.rand = rand;
		remainingZombies = level.getNumberOfZombies();
		zombiesAlived = remainingZombies;
		zombiesAppearences = 0;
	}

	// METHODS
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
		return rand.nextInt(GameWorld.NUM_ROWS);
	}
	// Returns the type of the available zombies
//	private int randomZombieType() {
////		return rand.nextInt(ZombieFactory.getAvailableZombies().size());
//		return 0;
//	}
	// Updates the appearences of the zombies in the game/match
	public void update() {
		addZombie();
	}
	// Returns true if it is possible to add a zombie to the game/match
	public boolean addZombie() {
		int row = randomZombieRow();
		return addZombie(row);
	}
	// Returns true if it is possible to add a zombie in the position (GameWorld.NUM_COLS, row). Otherwise returns false
	public boolean addZombie(int row) {
		boolean canAdd = getRemainingZombies() > 0 && shouldAddZombie() && isPositionEmpty(GameWorld.NUM_COLS, row);
//		int zombieType = randomZombieType();
		if (canAdd) {
			Zombie z = new Zombie(this.game, GameWorld.NUM_COLS, row);
			if (this.game.addZombie(z)) {
				zombiesAppearences++;				
			}
			else {
				canAdd = false;
			}
		}
		return canAdd;
	}
	// Returns the quantity of remaining zombies that have not appeared in the game/match yet
	public static int getRemainingZombies() {
		return remainingZombies - zombiesAppearences;
	}
	// Returns true if the position (numCols, row) is empty. Otherwise returns false
	private boolean isPositionEmpty(int numCols, int row) {
		return (game.getGameItemInPosition(numCols, row) == null);
	}
	// Returns true if all the zombies are dead. Otherwise returns false
	public static boolean areAllZombiesDead() {
		return (zombiesAlived == 0);
	}
	// Returns true if a zombie arrives the position (-1, row). Otherwise returns false
	public static boolean arrival() {
		return GameObjectContainer.getZombiesArrival();
	}
	// Updates the quantity of zombies alived
	public static void setZombiesAlived() {
		zombiesAlived--;
	}
}