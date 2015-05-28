package edu.statemachinegenerator;

import java.util.ArrayList;

public class GState {
	String stateId;
	String stateName;
	ArrayList<GTransition> transitions;
	
	public GState(String stateId, String stateName) {
		this.stateId = stateId;
		this.stateName = stateName;
		
		transitions = new ArrayList<GTransition>();
	}
	
	public String toString()
	{
		return "State " + this.stateName + "("+this.stateId+")";
	}
}
