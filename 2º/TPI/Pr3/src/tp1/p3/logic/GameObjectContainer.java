package tp1.p3.logic;

import java.util.ArrayList;
import java.util.List;

import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.gameobjects.GameObject;
import tp1.p3.view.Messages;

public class GameObjectContainer {

	// ATRIBUTES
	private List<GameObject> gameObjects;
	private GameWorld game;
	
	// BUILDER
	public GameObjectContainer(GameWorld game) {
		this.game = game;
		this.gameObjects = new ArrayList<>();
	}
	
	// METHODS
	// Returns the status of the game object in the position (col, row)
	public String positionToString(int col, int row) {
		StringBuilder buffer = new StringBuilder();
		boolean sunPainted = false;
		boolean sunAboutToPaint = false;
		for (GameObject g : gameObjects) {
			if(g.isAlive() && g.getCol() == col && g.getRow() == row) {
				String objectText = g.toString();
				sunAboutToPaint = objectText.indexOf(Messages.SUN_SYMBOL) >= 0;
				if (sunAboutToPaint) {
					if (!sunPainted) {
						buffer.append(objectText);
						sunPainted = true;
					}
				} else {
					buffer.append(objectText);
				}
			}
		}
		return buffer.toString();
	}
	// Returns true if a game object has been removed of the list. Otherwise returns false
	public boolean removeDead() {
		boolean ok = false;
		for (int i = 0; i < gameObjects.size(); i++) {
			GameObject o = gameObjects.get(i);
			if(!o.isAlive()) {
				o.onExit();
				gameObjects.remove(o);
				ok = true;
			}
		}
		return ok;
	}
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
					if (this.isFullyOccupied(col, row)) {
						gameObject = gameObjects.get(i);
						if (!gameObject.fillPosition()) { // no sé si puede funcionar bien esto
							found = false;
							i++;
							gameObject = null;
						}
					}
				}
			}
		}
		return gameObject;
	}
	// Returns true if it is possible to add the 'item' to the list. Otherwise returns false
	public boolean addObject(GameObject item) { 
		if (!item.fillPosition()) {
			return this.gameObjects.add(item);
		}
		else {
			GameObject obj = this.searchGameObject(item.getCol(), item.getRow());
			if (obj == null) {
				if (item.getCost() <= game.getSuncoins()) {
					 return this.gameObjects.add(item);
				}
			}
		}
		return false;
	}
	// Empties the gameObject list
	public void EmptyList() {
		this.gameObjects.removeAll(gameObjects);
	}
	// Updates the GameObject that are in the game/match
	public void Update() throws GameException {
		GameObject obj;
		for (int i = 0; i < this.gameObjects.size(); i++) {
			obj = this.gameObjects.get(i);
			obj.update();
			if (!obj.isAlive()) {
				this.gameObjects.remove(i);
				i--;
			}
		}
	}
	// Returns true if a zombie arrives the position (-1, row). Otherwise returns false
	public boolean getZombiesArrival() {
		int i = 0;
		boolean found = false;
		GameItem item;
		while ((i < GameWorld.NUM_ROWS) && !found) {
			item = this.game.getGameItemInPosition(-1, i);
			found = (item != null);
			if (!found) {
				i++;
			}
		}
		return found;
	}
	// Returns true if the position (col, row) is ocupied by a different game object of the sun. Otherwise returns false 
	public boolean isFullyOccupied(int col, int row) {
		int i = 0;
		boolean fullyOcuppied = false;
		while (i < this.gameObjects.size() && !fullyOcuppied) {
			GameObject g = this.gameObjects.get(i);
			if (g.isAlive() && g.isInPosition(col, row)) {
				fullyOcuppied = g.fillPosition();
			}
			i++;
		}
		return fullyOcuppied;
	}
	// Returns true if it is possible to catch one or several objects in the position (col, row). Otherwise returns false
	public boolean tryToCatchObject(int col, int row) {
		boolean found = false;
		GameObject obj;
		for (int i = 0; i < this.gameObjects.size(); i++) {
			obj = this.gameObjects.get(i);
			if (obj.getCol() == col && obj.getRow() == row && obj.catchObject()) {
				found = true;
			}
		}
		return found;
	}
}