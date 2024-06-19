package tp1.p3.control.exceptions;

public class CommandExecuteException extends GameException {

	/**
	 * 
	 */
	private static final long serialVersionUID = 5070561988758912645L;
	
	public CommandExecuteException(String message) {
		super(message);
	}
	
	public CommandExecuteException(Throwable cause) {
		super(cause);
	}

	public CommandExecuteException(String message, Throwable cause) {
		super(message, cause);
	}

}
