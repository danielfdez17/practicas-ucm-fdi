package tp1.p3.logic;

import java.util.Random;

import tp1.p3.control.Level;
import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.gameobjects.Zombie;
import tp1.p3.logic.gameobjects.ZombieFactory;

/**
 * Manage zombies in the game.
 *
 */
public class ZombiesManager {

	// ATRIBUTES
	private GameWorld game;
	private Level level;
	private Random rand;
	private int remainingZombies;
	private int zombiesAlived;
	private int zombiesAppearences;

	// BUILDER
	public ZombiesManager(GameWorld game, Level level, Random rand) {
		this.game = game;
		this.level = level;
		this.rand = rand;
		this.remainingZombies = level.getNumberOfZombies();
		this.zombiesAlived = remainingZombies;
		this.zombiesAppearences = 0;
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
	// Returns a random int that represents one of available zombies
	private int randomZombieType() {
		return rand.nextInt(ZombieFactory.getAvailableZombies().size());
	}
	// Updates the appearences of the zombies in the game/match
	public void update() throws GameException {
		addZombie();
	}
	// Returns true if it is possible to add a zombie to the game/match
	public boolean addZombie() throws GameException {
		int row = randomZombieRow();
		return addZombie(row);
	}
	// Returns true if it is possible to add a zombie in the position (GameWorld.NUM_COLS, row). Otherwise returns false
	public boolean addZombie(int row) throws GameException {
		boolean canAdd = getRemainingZombies() > 0 && shouldAddZombie() && !isObjcetInPosition(GameWorld.NUM_COLS, row);
		int zombieType = randomZombieType();
		if (canAdd) {
			Zombie z = ZombieFactory.spawnZombie(zombieType, game, GameWorld.NUM_COLS, row);
			if (z != null) {
				if (!this.game.isFullyOcuppied(z.getCol(), z.getRow())) { // creo que no hace falta porque en la col 8 no se pueden spawnear plantas ni soles
					if (this.game.addItem(z, false)) {
						zombiesAppearences++;				
					}
					else {
						canAdd = false;
					}					
				}
			}
		}
		return canAdd;
	}
	// Returns true if the position (numCols, row) is empty. Otherwise returns false
	private boolean isObjcetInPosition(int numCols, int row) {
		return (game.getGameItemInPosition(numCols, row) != null);
	}
	// Returns the quantity of remaining zombies that have not appeared in the game/match yet
	public int getRemainingZombies() {
		return this.remainingZombies - this.zombiesAppearences;
	}
	// Returns true if all the zombies are dead. Otherwise returns false
	public boolean areAllZombiesDead() {
		return (this.zombiesAlived == 0);
	}
	// Returns true if a zombie arrives the position (-1, row). Otherwise returns false
	public boolean arrival() {
		return this.game.getZombiesArrival();
	}
	// Updates the quantity of zombies alived
	public void setZombiesAlived() {
		this.zombiesAlived--;
	}
}