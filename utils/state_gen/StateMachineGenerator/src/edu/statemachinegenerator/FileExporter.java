package edu.statemachinegenerator;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class FileExporter {
	public static String stateFile = "stateList.h";
	public static String transitionFile = "transitions.h";
	
	static void exportFile(String outputPath, ArrayList<GState> states, ArrayList<GTransition> transitions)
	{
		writeStateFile(outputPath, states, transitions);
		
		System.out.println("remove duplicate transitions");
		ArrayList<GTransition> transitionsToRemove = new ArrayList<GTransition>();
		for(GTransition transition : transitions)
		{ for(GTransition trans2 : transitions) {
			if(trans2.name.equals(transition.name) && !trans2.equals(transition)) transitionsToRemove.add(trans2);
		}}
		
		transitions.removeAll(transitionsToRemove);
		System.out.println(transitions.size() + " unique transitions remaining.");
		
		writeTransitionFile(outputPath, states, transitions);
	}
	
	static private void writeStateFile(String outputPath, ArrayList<GState> states, ArrayList<GTransition> transitions)
	{
		try {
			if(outputPath.charAt(outputPath.length()-1) != '/') outputPath += "/";
			System.out.print("Write statefile to " + outputPath + stateFile+"..");
			
			PrintWriter writer = new PrintWriter(outputPath + stateFile, "UTF-8");
			DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
			Date date = new Date();
			
			writer.println("/* Generated States File \n");
			writer.println(" * Date: "+dateFormat.format(date));
			writer.println(" * "+states.size() + " states");
			writer.println(" * "+transitions.size() + " transitions");
			writer.println(" */\n");
			
			writer.println("#ifndef STATELIST_H_\n#define STATELIST_H_\n");
			writer.println("#include "+'"'+"State.cpp"+'"');
			writer.println("#include "+'"'+"Context.cpp"+'"'+"\n\n");
			writer.println("/* States */");

			
			for(GState state : states) {
				String sname = state.stateName;
				
				writer.println("class "+sname+": public State{");
				writer.println("public:");
				writer.println("\t"+sname+"(Context* con);");
				writer.println("\tvirtual ~"+sname+"();");
				//Transitions
				for(GTransition transition : state.transitions) {
					writer.println("\tvirtual void "+transition.name+"(void);");
				}
				writer.println("private:");
				writer.println("\t"+sname+"(const "+sname+"& other);");
				writer.println("\t"+sname+"& operator=(const "+sname+"& other);");
				writer.println("};");
				writer.println("\n");
			}
			
			writer.println("\n#endif // STATELIST_H_");
			writer.close();
			System.out.println("done.");
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	static private void writeTransitionFile(String outputPath, ArrayList<GState> states, ArrayList<GTransition> transitions)
	{
		try {
			if(outputPath.charAt(outputPath.length()-1) != '/') outputPath += "/";
			System.out.print("Write statefile to " + outputPath + stateFile+"..");
			
			PrintWriter writer = new PrintWriter(outputPath + transitionFile, "UTF-8");
			DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
			Date date = new Date();
			
			System.out.print("Write transitionfile to " + outputPath + transitionFile+"..");
			
			writer.println("/* Generated Transition File \n");
			writer.println(" * Date: "+dateFormat.format(date));
			writer.println(" * "+transitions.size() + " transitions");
			writer.println(" */\n");
			
			writer.println("#ifndef TRANSITIONLIST_H_\n#define TRANSITIONLIST_H_\n\n");
			writer.println("class Transitions{");
			writer.println("\tpublic:");
			
			for(GTransition transition : transitions) {
				writer.println("\t\tvirtual void "+transition.name+"(void) = 0;");
			}
			
			writer.println("};");
			writer.println("\n");
			writer.println("\n#endif // TRANSITIONLIST_H_");
			writer.close();
			System.out.println("done");
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
