package tp1.p2.logic;

import java.util.ArrayList;
import java.util.List;

import tp1.p2.logic.gameobjects.Peashooter;
import tp1.p2.logic.gameobjects.Plant;
import tp1.p2.logic.gameobjects.Sunflower;
import tp1.p2.logic.gameobjects.Zombie;
import tp1.p2.logic.gameobjects.GameObject;
import tp1.p2.logic.gameobjects.PlantFactory;

public class GameObjectContainer {

	// ATRIBUTES
	private List<GameObject> gameObjects;
	private String plantName;
	private static GameWorld game;
	private int col;
	private int row;

	// BUILDER
	public GameObjectContainer(GameWorld gameWorld) {
		gameObjects = new ArrayList<>();
		game = gameWorld;
	} 
	//	Plant plant = PlantFactory.spawnPlant(plantName, game, col, row);
	// METHODS
	// Returns a copy of the GameObject in the position (col, row). Otherwise returns null
	public GameObject searchGameObject(int col, int row) {
		GameObject gameObject = null;
		boolean found = false;
		int i = 0;
		if (!this.gameObjects.isEmpty()) {
			while ((i < gameObjects.size()) && !found) {
				found = gameObjects.get(i).isInPosition(col, row);
				if (!found) {
					i++;
				}
				else {
					gameObject = gameObjects.get(i);
				}
			}
		}
		return gameObject;
	}
	// Returns true if it is possible to add the 'obj' to the list. Otherwise returns false
	public boolean addObject(GameObject obj) {
		if (searchGameObject(obj.getCol(), obj.getRow()) == null) {
			if (obj.getCost() <= game.getSuncoins()) {
				this.gameObjects.add(obj);			
				game.setSuncoins(obj.getCost());
			}
			return true;
		}
		return false;
	}
	// Empties the gameObject list
	public void EmptyList() {
		this.gameObjects.removeAll(gameObjects);
	}
	// Updates the GameObject that are in the game/match
	public void Update() {
		GameObject obj;
		for (int i = 0; i < this.gameObjects.size(); i++) {
			obj = this.gameObjects.get(i);
				obj.update();				
				if (!obj.isAlive()) {
					this.gameObjects.remove(obj);
				}
		}
	}
	// Returns true if a zombie arrives the position (-1, row). Otherwise returns false
	public static boolean getZombiesArrival() {
		int i = 0;
		boolean found = false;
		GameItem item;
		while ((i < GameWorld.NUM_ROWS) && !found) {
			item = game.getGameItemInPosition(-1, i);
			found = (item != null);
			if (!found) {
				i++;
			}
		}
		return found;
	}
}