package edu.statemachinegenerator;

public class GeneratorMain {
	static String inputFile = "/Users/ibosy/Documents/studium/se/temp/xml_test.xml";
	static String outputPath = "/Users/ibosy/Documents/studium/se/temp/gen";
	
	public static void main(String[] args) {
		int nullTransitionCount = 0;
		
		System.out.println("read xml from " + inputFile + "...");
		GXMLReader xmlHandler = new GXMLReader();  
		xmlHandler.getXml(inputFile);

		System.out.println("link states/transitions");
		for(GTransition transition : xmlHandler.transitions)
		{
			transition.fromState = xmlHandler.getStateById(transition.from);
			transition.toState = xmlHandler.getStateById(transition.to);
			if(transition.fromState != null) {
				transition.fromState.transitions.add(transition);
			} else {
				nullTransitionCount++;
			}
		}
		
		System.out.println("clean names");
		for(GState state : xmlHandler.states) state.stateName = cleanName(state.stateName);
		for(GTransition transition : xmlHandler.transitions) transition.name = cleanName(transition.name);
		
		System.out.println("exporting " + xmlHandler.states.size() + " states and " + xmlHandler.transitions.size() + " transitions.");
		FileExporter.exportFile(outputPath, xmlHandler.states, xmlHandler.transitions);
		
		System.out.println("Export complete!");
		if(nullTransitionCount!=1) System.out.println("Warning: Found "+nullTransitionCount+" transitions without origin (ignored).");
	}
	
	private static String cleanName(String inName)
	{
		String outName = inName;
		if(outName.contains("@"))
		{
			outName = outName.substring(0, outName.indexOf('@'));
		}
		outName = outName.replace(" ", "_").replace(":", "_").replace("(","")
				.replace(")","").replace("?", "").replace("/", "").replace("&", "and")
				.replace("!", "").replace("[","").replace("]", "").replace("ö", "oe")
				.replace("ä", "ae").replace("ü", "ue").replace("Ä", "AE").replace("Ö", "OE")
				.replace("Ü", "UE");

		return outName;
	}

}
