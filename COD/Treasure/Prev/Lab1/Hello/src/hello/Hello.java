package hello;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.StringTokenizer;
import java.util.Vector;

public class Hello {
    public static void main(String[] args) throws IOException {
        String input="C:\\Users\\Aturag\\Documents\\NetBeansProjects\\Hello\\src\\hello\\cprog.txt";
        FileReader fr=new FileReader(input);
        BufferedReader br=new BufferedReader(fr);
        String output="C:\\Users\\Aturag\\Documents\\NetBeansProjects\\Hello\\src\\hello\\cprog_1.txt";
        FileWriter fw=new FileWriter(output);
        BufferedWriter bw =new BufferedWriter(fw);
        String line,reed=null;
        /*********** Removing Comments **********/
        while((line=br.readLine())!=null) {
            reed=line;
            if(reed.startsWith("//")||reed.length()==0) continue;
            if(reed.startsWith("/*")) {
                while((line=br.readLine())!=null) {
                   reed=line;
                   if(reed.startsWith("*/")) break;
                }
                continue;
            }
            fw.write(reed);
            fw.write("\r\n");
        }
        fw.close();
        /********* End *********************/
        String [] keys = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
        HashMap<String,Integer> hm = new HashMap<String,Integer>();
        for(int i=0;i<keys.length;i++) {
            hm.put(keys[i],1);
        }
        fr=new FileReader(output);
        br=new BufferedReader(fr);
        line=reed=null;
        String [] red = new String[100];
        int l=0;
        while((line=br.readLine())!=null) {
            red[l++]=line;
            System.out.println(red[l-1]);
        }
        
        /******* keywords *********/
        Vector keytokens = new Vector();
        Vector strtokens = new Vector();
        Vector delimtokens = new Vector();
        Vector consttokens = new Vector();
        Vector idtokens = new Vector();
        Vector optokens = new Vector();
                
        for(int i=0;i<l;i++) {
            int j=0;  //System.out.println(j);
            while(j<red[i].length()) {
                String plus="";
                while(red[i].charAt(j)!=' ') {
                    plus+=red[i].charAt(j);
                    j++;
                    if(j>=red[i].length()) break;
                } 
                while(j<red[i].length()&&red[i].charAt(j)==' ') {
                    j++;
                    if(j>=red[i].length()) break;
                }
                if(plus.startsWith("#include")||plus.startsWith("<stdio.h>")) continue;
                if(hm.containsKey(plus)==true) {
                    keytokens.add(plus);
                    //System.out.println(plus);
                }
                else {
                    if(plus.startsWith("\"")) {
                        strtokens.add(plus.substring(1));
                        continue;
                      //  System.out.println(strtokens.get(strtokens.size()-1));
                    }
                    else if(plus.endsWith("\"")) {
                        String hh="";
                       // for(int m=0;m<plus.length();m++) hh+=plus.charAt(m);
                        strtokens.add(plus);
                        continue;
                        //System.out.println(plus);
                    }
                    else if(plus.startsWith("(")) {
                       delimtokens.add("(");
                       continue;
                    }
                    else if(plus.startsWith(")")) {
                        delimtokens.add(")");
                       continue;
                    }
                    else if(plus.startsWith("{")) {
                       delimtokens.add("{");
                       continue;
                    }
                    else if(plus.endsWith("}")) {
                       delimtokens.add("}");
                       continue;
                    }
                    else if(plus.endsWith(")")) {
                       delimtokens.add(")");    
                       continue;
                    }
                    else if(plus.contentEquals("+")||plus.contentEquals("-")||plus.contentEquals("^")||plus.contentEquals("*")||plus.contentEquals("++")||plus.contentEquals("--")||plus.contentEquals("&&")||plus.contentEquals("||")||plus.contentEquals("%")||plus.contentEquals("!")||plus.contentEquals("!=")||plus.contentEquals(">=")||plus.contentEquals("<=")||plus.contentEquals("==")||plus.contentEquals("=")||plus.contentEquals(">")||plus.contentEquals("<")) {
                        optokens.add(plus);
                        continue;
                    }
                    else if(plus.matches(";")) {
                        continue;
                    }
                    else {
                    int h=plus.length();
                    for(int k=0;k<plus.length();k++) {
                        if(plus.charAt(k)>='0'&&plus.charAt(k)<='9') h--;
                        else break;
                    }
                    if(h==0) {
                       consttokens.add(plus);
                    }
                    else {
                        idtokens.add(plus);
                    }
                    }
                }
                
            }  
        }
        
        
        System.out.print("KeyWords:  ");
            for(int k=0;k<keytokens.size();k++) {
                System.out.print(keytokens.get(k)+" ");  
            }
            System.out.println();
            
            System.out.print("Strings:  ");
            for(int k=0;k<strtokens.size();k++) {
                System.out.print(strtokens.get(k)+" ");  
            }
            System.out.println();
            
            System.out.print("delimiters:  ");
            for(int k=0;k<delimtokens.size();k++) {
                System.out.print(delimtokens.get(k)+" ");  
            }
            System.out.println();
            
            System.out.print("id's:  ");
            for(int k=0;k<idtokens.size();k++) {
                System.out.print(idtokens.get(k)+" ");  
            }
            System.out.println();
            
            System.out.print("constants:  ");
            for(int k=0;k<consttokens.size();k++) {
                System.out.print(consttokens.get(k)+" ");  
            }
            System.out.println();
            
            System.out.print("Operators:  ");
            for(int k=0;k<optokens.size();k++) {
                System.out.print(optokens.get(k)+" ");  
            }
            System.out.println();
            
        /************ end ***************/
        
        
    }
    
}