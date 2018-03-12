/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package create_tokenizer;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Aturag
 */
public class comment_removal {
     void read() throws IOException{
        String a[] = {"int","float","double","void","long","long double"}; 
         int count  = 0;
         String y[] = null;
       //  FileWriter f1 = new FileWriter();
         FileReader f;
         try {
             f = new FileReader("input.c");
             BufferedReader br = new BufferedReader(f);
            String content,words;
            int k  = 0;
            int s;
            File file1 = new File("newfile.c");
 
	// if file doesnt exists, then create it
	       if (!file1.exists()) {
		    file1.createNewFile();
        	}
 
	     FileWriter fw = new FileWriter(file1.getAbsoluteFile());
	     BufferedWriter bw = new BufferedWriter(fw);
          //    StringBuilder newCode = new StringBuilder();
            
                  boolean inBlockComment = false;
                  boolean inLineComment = false;
                  boolean out = true;
                  boolean inquotes = false;

                int prev = br.read();
                 int cur;
                String t = "";
               
             //   System.out.println("hello");
                 for(cur = br.read(); cur != -1; cur = br.read()) {
                        
                        if(inBlockComment) {
                            if (prev == '*' && cur == '/') {
                                inBlockComment = false;
                                out = false;
                            }
                        } else if (inLineComment) {
                            if (cur == '\r') { // start untested block
                                br.mark(1);
                                int next = br.read();
                                if (next != '\n') {
                                     br.reset();
                                }
                                inLineComment = false;
                                out = false; // end untested block
                            } else if (cur == '\n') {
                                 inLineComment = false;
                                 out = false;
                            }
                        }else if(inquotes){
                           if(cur == '\"'){
                              inquotes = false;
                              out = false;                           
                             
                           }                   
                            
                        }else {
                                if (prev == '/' && cur == '*') {
                                    
                                    br.mark(1); // start untested block
                                    int next = br.read();
                                    if (next != '*') {
                                         inBlockComment = true; // tested line (without rest of block)
                                    }
                                   br.reset(); // end untested block
                                } else if (prev == '/' && cur == '/') {
                                     inLineComment = true;
                                } /*else if(cur == '\"'){
                                      inquotes = true;
                                      
                                }*/else if (out){
                                      t += (char)prev;
                                      //  newCode.append((char)prev);
                                } else {
                                    out = true;
                                }
                        }
                    prev = cur;
                 }
              //   System.out.println(t);
                bw.write(t);
                 
             
             
             bw.close();
         
         }catch (FileNotFoundException ex) {
             Logger.getLogger(comment_removal.class.getName()).log(Level.SEVERE, null, ex);
         }
         
     }
    
}
