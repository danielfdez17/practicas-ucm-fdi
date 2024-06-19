package tp1.p3.logic.gameobjects;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.GameWorld;
import tp1.p3.view.Messages;

public class PlantFactory {

	// CONSTANT
	/* @formatter:off */
	private static final List<Plant> AVAILABLE_PLANTS = Arrays.asList(
		new Sunflower(),
		new Peashooter(),
		new WallNut(),
		new CherryBomb()
	);
	/* @formatter:on */

	// METHODS
	// Returns true if the 'plantName' matches witha an existing plant. Otherwise returns false
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
	// Returns a plant that matches with 'plantName'. Otherwise returns null
	public static Plant spawnPlant(String plantName, GameWorld game, int col, int row) throws GameException {
		if (!isValidPlant(plantName)) {
			throw new GameException(Messages.INVALID_GAME_OBJECT);
		}
		else {
			for (Plant p : AVAILABLE_PLANTS) {
				if (p.getSymbol().equalsIgnoreCase(plantName) || p.getName().equalsIgnoreCase(plantName)) {
					return p.spawn(game, col, row);
				}
			}
			return null;			
		}
	}
	// Shows the information of every plant
	public static void ShowPlantsInfo() {
		for (Plant p : AVAILABLE_PLANTS) {
			System.out.println(p.getDescription());
		}
	}

	public static Iterable<Plant> getAvailablePlants() {
		return Collections.unmodifiableList(AVAILABLE_PLANTS);
	}

	/*
	 * Avoid creating instances of this class
	 */
	private PlantFactory() {
	}
}