package tp1.p2.logic.gameobjects;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import tp1.p2.logic.GameWorld;
// guarda en una única lista TODAS las plantas
public class PlantFactory {
	/*
	 * Avoid creating instances of this class
	 */
	
	// CONSTANTS
	/* @formatter:off */
	private static final List<Plant> AVAILABLE_PLANTS = Arrays.asList(
		new Sunflower(),
		new Peashooter()
	);
	/* @formatter:on */
	// ATRIBUTES
	private static GameWorld game;
	private static int col;
	private static int row;

	// BUILDER
	private PlantFactory() {
	}
	
	// METHODS
	// Shows the information of all the available plants
	public static void ShowPlantsInfo() {
		for (Plant p : AVAILABLE_PLANTS) {
			System.out.println(p.getDescription());
		}
	}
	// Returns true if a plant is valid. Otherwise returns false
	public static boolean isValidPlant(String plantName) {
		boolean valid = false;
		for (Plant p : AVAILABLE_PLANTS) {
			valid = (p.getSymbol().equalsIgnoreCase(plantName) || p.getName().equalsIgnoreCase(plantName));
			if (valid) {
				return valid;
			}
		}
		return valid;
	}
	// Returns a copy of a plant if is valid. Otherwise returns null
	public static Plant spawnPlant(String plantName, GameWorld game, int col, int row) {
		Plant p = null;
		if (isValidPlant(plantName)) {
			switch(plantName) {
			case "p":
			case "peashooter":
				p = new Peashooter(game, col, row);
				break;
			case "s":
			case "sunflower":
				p = new Sunflower(game, col, row);
				break;
			}
		}
		return p;
	}
	// Returns the name of the available plants
	public static List<Plant> getAvailablePlants() {
		return Collections.unmodifiableList(AVAILABLE_PLANTS);
	}
}