package edu.statemachinegenerator;

import java.util.ArrayList;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class GXMLReader extends DefaultHandler{

	ArrayList<GState> states = new ArrayList<GState>();
    ArrayList<GTransition> transitions = new ArrayList<GTransition>();
    
    public GState getStateById(String id)
    {
    	for(GState state : states) {
    		if(state.stateId.equalsIgnoreCase(id)) return state;
    	}
    	
    	return null;
    }
    
    public GTransition getTransitionById(String id) {
    	for(GTransition transition : transitions)
    	{
    		if(transition.id.equalsIgnoreCase(id)) return transition;
    	}
    	
    	return null;
    }
    
	public void getXml(String inputFile){
	  try {
	   // obtain and configure a SAX based parser
	   SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();
	
	   // obtain object for SAX parser
	   SAXParser saxParser = saxParserFactory.newSAXParser();
	
	   // default handler for SAX handler class
	   // all three methods are written in handler's body
	   DefaultHandler defaultHandler = new DefaultHandler(){
	    
	    boolean isInModels = false;
	    boolean wasInModels = false;
	    
	    // this method is called every time the parser gets an open tag '<'
	    // identifies which tag is being open at time by assigning an open flag
	    public void startElement(String uri, String localName, String qName,
	      Attributes attributes) throws SAXException {
	   
	    	if(qName.equalsIgnoreCase("Models")) {
	    		isInModels = true;
	    		System.out.println("found models");
	    	} else if(isInModels && qName.equalsIgnoreCase("State2")) {
	    		String id = attributes.getValue("Id");
	    		if(id == null || id.isEmpty()) return;
		    	String stateName = attributes.getValue("Name");
		    	GState newState = new GState(id, stateName);
		    	states.add(newState);
		    } else if(isInModels && qName.equalsIgnoreCase("Transition2"))
		    {
		    	String id = attributes.getValue("Id");
	    		if(id == null || id.isEmpty()) return;
		    	String transitionName = attributes.getValue("Name");
		    	if (transitionName == null) transitionName = "";
		    	String from = attributes.getValue("From");
		    	String to = attributes.getValue("To");
		    	GTransition newTransition = new GTransition(id, transitionName, from, to);
		    	transitions.add(newTransition);
		    }
		    
	    
	    }
	
	    // prints data stored in between '<' and '>' tags
	    public void characters(char ch[], int start, int length)
	      throws SAXException {
	     
	    }
	
	    // calls by the parser whenever '>' end tag is found in xml 
	    // makes tags flag to 'close'
	    public void endElement(String uri, String localName, String qName)
	      throws SAXException {
	    	if(isInModels && qName.equalsIgnoreCase("Models"))
	    	{
	    		isInModels = false;
	    	}
	    }
	   };
	   
	   // parse the XML specified in the given path and uses supplied
	   // handler to parse the document
	   // this calls startElement(), endElement() and character() methods
	   // accordingly
	   saxParser.parse(inputFile, defaultHandler);
	  } catch (Exception e) {
	   e.printStackTrace();
	  }
	}
}

