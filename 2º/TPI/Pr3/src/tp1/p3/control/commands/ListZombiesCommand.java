package tp1.p3.control.commands;

import tp1.p3.control.Command;
import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.GameWorld;
import tp1.p3.logic.gameobjects.ZombieFactory;
import tp1.p3.view.Messages;

public class ListZombiesCommand extends Command {

	// METHODS
	@Override
	protected String getName() {
		return Messages.COMMAND_LIST_ZOMBIES_NAME;
	}
	@Override
	protected String getShortcut() {
		return Messages.COMMAND_LIST_ZOMBIES_SHORTCUT;
	}
	@Override
	public String getDetails() {
		return Messages.COMMAND_LIST_ZOMBIES_DETAILS;
	}
	@Override
	public String getHelp() {
		return Messages.COMMAND_LIST_ZOMBIES_HELP;
	}
	@Override
	public boolean execute(GameWorld game) throws GameException {
		System.out.println(Messages.AVAILABLE_ZOMBIES);
		ZombieFactory.ShowZombiesInfo();
		System.out.println();
		return true;
	}
}