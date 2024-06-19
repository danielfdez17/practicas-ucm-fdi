package tp1.p3.control.exceptions;

public class CommandParseException extends GameException {

	/**
	 * 
	 */
	private static final long serialVersionUID = 8468022554495642947L;

	public CommandParseException(String message) {
		super(message);
	}
	
	public CommandParseException(Throwable cause) {
		super(cause);
	}

	public CommandParseException(String message, Throwable cause) {
		super(message, cause);
	}

}
