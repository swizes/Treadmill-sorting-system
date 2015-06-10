package edu.statemachinegenerator;

public class GTransition {
	String id;
	String name;
	String from;
	String to;
	GState fromState;
	GState toState;
	
	public GTransition(String id, String name, String from, String to) {
		this.id = id;
		this.name = name;
		this.from = from;
		this.to = to;
	}
	
	public String toString()
	{
		return "Transition " + this.name + "(" + this.id + ")" + (fromState == null ? "NULL" : fromState.stateName) + " -> " + (toState == null ? "NULL" : toState.stateName);
	}
}
