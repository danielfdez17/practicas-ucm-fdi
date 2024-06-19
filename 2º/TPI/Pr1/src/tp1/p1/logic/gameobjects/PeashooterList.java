package tp1.p1.logic.gameobjects;

import java.lang.System.Logger.Level;

import tp1.p1.logic.Game;
import tp1.p1.view.Messages;

public class PeashooterList {
	
	// CONSTANTS
	public static final int MAX_PEASHOOTERS = 100;
	
	// ATRIBUTES
	private static Peashooter[] peashooters;
	private static int numPeashooters;
	
	// BUILDERS
	// Builder for the peashooter list
	public PeashooterList() {
		peashooters = new Peashooter[MAX_PEASHOOTERS];
		numPeashooters = 0;
	}
	//METHODS
	// Returns if it is posible to add a new peahooter to the game. If it is posible, adds the plant and returns true; in other cases returns false
	public static boolean addPeashooter(Peashooter p) {
		boolean found = searchPeashooter(p.getCol(), p.getRow());
		if (!found && (numPeashooters < MAX_PEASHOOTERS)) {
			peashooters[numPeashooters] = p;
			numPeashooters++;			
		}
		else {
			System.out.println(Messages.INVALID_POSITION);
		}
		return !found;
	}
	// Looks for a peashooter in the position col,row. If a peashooter is found, returns true; in other cases returns false
	public static boolean searchPeashooter(int col, int row) {
		boolean found = false;
		int i = 0;
		while ((i < numPeashooters) && !found) {
			found = ((peashooters[i].getCol() == col) && (peashooters[i].getRow() == row) && peashooters[i].isAlive());
			i++;
		}
		return found;
	}
	// Looks for the peashooter which is in the position col,row and shows it's icon
	public static String searchPeashooterICON(int col, int row) {
		String string;
		boolean found = false;
		int i = 0;
		while ((i < numPeashooters) && !found) {
			found = ((peashooters[i].getCol() == col) && (peashooters[i].getRow() == row) && peashooters[i].isAlive());
			if (!found) {
				i++;				
			}
		}
		string = Messages.PEASHOOTER_ICON.formatted(peashooters[i].getEndurance());
		return string;
	}
	// Updates the endurance of the peashooter that is in the position 'col,row'
	public static void zombieDamagePeashooter(int col, int row) {
		boolean found = false;
		int i = 0;
		while ((i < numPeashooters) && !found) {
			found = ((peashooters[i].getCol() == col) && (peashooters[i].getRow() == row) && peashooters[i].isAlive());
			if (!found) {
				i++;				
			}
		}
		if (found) {
			damagePeashooter(i);			
		}
	}
	// The peashooter in the position 'i' gets damaged
	private static void damagePeashooter(int i) {
		peashooters[i].setEndurance(Zombie.DAMAGE);
	}
	// Updates the peashooters state
	public void Update() {
		for (int i = 0; i < numPeashooters; i++) {
			if (peashooters[i].isAlive()) {
				peashooters[i].shootZombie();
				peashooters[i].setIsAlive();
			}
		}
	}
}