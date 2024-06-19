package tp1.p1.logic.gameobjects;

import tp1.p1.logic.Game;
import tp1.p1.logic.ZombiesManager;
import tp1.p1.view.Messages;


public class ZombieList {
	
	// CONSTANTS
	public static final int MAX_ZOMBIES = 10;
	
	// ATRIBUTES
	private static Zombie[] zombies;
	private static int numZombies;
	private static int remainingZombies;
	
	// BUILDERS
	// Builder for the zombie list
	public ZombieList(int remainingZombies) {
		ZombieList.remainingZombies = remainingZombies;
		if (ZombieList.remainingZombies <= MAX_ZOMBIES) {
			zombies = new Zombie[ZombieList.remainingZombies];
			numZombies = 0;			
		}
	}
	
	// METHODS
	// Returns if it is posible to add a new zombie to the game. If it is posible, adds the zombie and returns true; in other cases returns false
	public static boolean addZombie(Zombie z) {
		boolean found = searchZombie(z.getCol(), z.getRow());
		if (!found && (numZombies < ZombieList.remainingZombies)) {
			zombies[numZombies] = z;
			numZombies++;
		}
		return !found;
	}
	// Looks for a zombie in the position col,row. If a zombie is found, returns true; in other cases returns false
	public static boolean searchZombie(int col, int row) {
		boolean found = false;
		int i = 0;
		while ((i < numZombies) && !found) {
			found = ((zombies[i].getCol() == col) && (zombies[i].getRow() == row) && zombies[i].isAlive());
			if (!found) {
				i++;
			}
		}
		return found;
	}
	// Looks for the zombie which is in the position col,row and shows it's icon
	public static String searchZombieICON(int col, int row) {
		String string;
		boolean found = false;
		int i = 0;
		while ((i < numZombies) && !found) {
			found = ((zombies[i].getCol() == col) && (zombies[i].getRow() == row) && zombies[i].isAlive());
			if (!found) {
				i++;
			}
		}
		string = Messages.ZOMBIE_ICON.formatted(zombies[i].getEndurance());
		return string;
	}
	// If a zombie reaches the last column, zombies win
	public boolean ZombiesWin() {
		boolean found = false;
		int i = 0;
		while ((i < numZombies) && !found) {
			found = (zombies[i].getCol() == - 1);
			i++;
		}
		return found;
	}
	// The zombie in the position 'col,row' gets damaged
	public static void damageZombie(int i) {
		zombies[i].setEndurance(Peashooter.DAMAGE);
	}
	// Returns true if all zombies are dead. Returns false in other cases
	public static boolean AllZombiesDead() {
		boolean win = false;
		int i = 0;
		while (i < numZombies && !win) {
			win = zombies[i].isAlive();
			i++;
		}
		return !win;
	}
	// Updates the endurance of the zombie that is in the position 'col,row'
	public static void peashooterDamageZombie(int col, int row) {
		boolean found = false;
		int i = 0;
		while ((i < numZombies) && !found) {
			found = ((zombies[i].getCol() == col) && (zombies[i].getRow() == row) && zombies[i].isAlive());
			if (!found) {
				i++;
			}
		}
		if (found) {
			damageZombie(i);			
		}
	}
	// Updates the remaining zombies when the zombies are inside the table
	public static void UpdateRemainingZombies() {
			ZombiesManager.UpdateZombiesAppearences();
		}
	// Updates the state of the zombies
		public void Update() { // si tiene una planta o zombie delante, no avanza haste que planta.isAlive() = false
			boolean is_peashooter, is_sunflower, is_zombie;
			for (int i = 0; i < numZombies; i++) {
				if (zombies[i].isAlive()) {
					is_peashooter = PeashooterList.searchPeashooter(zombies[i].getCol() - 1, zombies[i].getRow());
					is_sunflower = SunflowerList.searchSunflower(zombies[i].getCol() - 1, zombies[i].getRow());
					is_zombie = searchZombie(zombies[i].getCol() - 1, zombies[i].getRow());
					if (!is_peashooter && !is_sunflower && !is_zombie) {
						zombies[i].updatePosition();							
					}
					else if (is_peashooter) {
						PeashooterList.zombieDamagePeashooter(zombies[i].getCol() - 1, zombies[i].getRow());
					}
					else if (is_sunflower) {
						SunflowerList.zombieDamageSunflower(zombies[i].getCol() - 1, zombies[i].getRow());
					}
					zombies[i].addCycles();
					zombies[i].isAlive();							
				}
			}
		}
}