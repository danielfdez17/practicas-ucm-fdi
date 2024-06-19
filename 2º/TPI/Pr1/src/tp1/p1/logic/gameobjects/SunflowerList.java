package tp1.p1.logic.gameobjects;

import java.lang.System.Logger.Level;

import tp1.p1.logic.Game;
import tp1.p1.logic.gameobjects.ZombieList;
import tp1.p1.view.Messages;

public class SunflowerList {
	
	// CONSTATNS
	public static final int MAX_SUNFLOWERS = 100;
	
	// ATRIBUTES
	private static Sunflower[] sunflowers;
	private static int numSunflowers;
	private Zombie zombie;
	
	// BUILDERS
	// Builder for the sunflower list
	public SunflowerList() {
		sunflowers = new Sunflower[MAX_SUNFLOWERS];
		numSunflowers = 0;
	}
	
	// METHODS
	// Returns if it is posible to add a new sunflower to the game. If it is posible, adds the plant and returns true; in other cases returns false
	public static boolean addSunflower(Sunflower s) {
		boolean found = searchSunflower(s.getCol(), s.getRow());
		if (!found && (numSunflowers < MAX_SUNFLOWERS)) {
			sunflowers[numSunflowers] = s;
			numSunflowers++;			
		}
		else {
			System.out.println(Messages.INVALID_POSITION);
		}
		return !found;
	}
	// Looks for a sunflower in the position col,row. If a sunflower is found, returns true; in other cases returns false
	public static boolean searchSunflower(int col, int row) {
		boolean found = false;
		int i = 0;
		while ((i < numSunflowers) && !found) {
			found = ((sunflowers[i].getCol() == col) && (sunflowers[i].getRow() == row) && sunflowers[i].isAlive());
			i++;
		}
		return found;
	}
	// Looks for the sunflower which is in the position col,row and shows it's icon
	public static String searchSunflowerICON(int col, int row) {
		String string;
		boolean found = false;
		int i = 0;
		while ((i < numSunflowers) && !found) {
			found = ((sunflowers[i].getCol() == col) && (sunflowers[i].getRow() == row) && sunflowers[i].isAlive());
			if (!found) {
				i++;				
			}
		}
		string = Messages.SUNFLOWER_ICON.formatted(sunflowers[i].getEndurance());
		return string;
	}
	// Updates the endurance of the sunflower that is in the position 'col,row'
	public static void zombieDamageSunflower(int col, int row) {
		boolean found = false;
		int i = 0;
		while ((i < numSunflowers) && !found) {
			found = ((sunflowers[i].getCol() == col) && (sunflowers[i].getRow() == row) && sunflowers[i].isAlive());
			if (!found) {
				i++;				
			}
		}
		if (found) {
			damageSunflower(i);			
		}
	}
	// The peashooter in the position 'i' gets damaged
	private static void damageSunflower(int i) {
		sunflowers[i].setEndurance(Zombie.DAMAGE);
		
	}
	// Updates the sunflowers state
	public void Update() {
		for (int i = 0; i < numSunflowers; i++) {
			if (sunflowers[i].isAlive()) {				
				if (ZombieList.searchZombie(sunflowers[i].getCol() + 1, sunflowers[i].getRow())) {
					sunflowers[i].setEndurance(Zombie.DAMAGE);				
				}
				sunflowers[i].addCycles();
				sunflowers[i].addSuncoins();
				sunflowers[i].isAlive();
			}
		}
	}	
}