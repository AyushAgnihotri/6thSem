/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package create_tokenizer;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Vector;

/**
 *
 * @author Aturag
 */
public class token_token {
    void make_token() throws FileNotFoundException, IOException {
        FileReader f = new FileReader("newfile.c");
        BufferedReader br = new BufferedReader(f);
        String vari[] = {"int","float","double","void","long long"};
        String key[] = {"int","float","double","void","long long","printf","if","else", "scanf", "main","for", "while","continue","break"};
        String delim[] = {"(", ")","{","}"};
        String oper[] = {"-=","+=","*=","/=","%=","==","=","*","++","+","--", "-","/","^","&","%","|","<=",">=",">","<","&&","||","&","|"};
        String spec[] = { "%d", "%lld", "%lf", "%f", "%s", "%c"};
        Vector<String> string = new Vector<String>();
        Vector<String> variable = new Vector<String>();
        String content = br.readLine();
        while(content != null) {
            content = content.trim();
            int i,curr = 0,flag = 0;
           // System.out.println(content);
            for(i = 0;i < vari.length;i++) {
                    if(curr + vari[i].length() - 1 < content.length()) {
                        String temp = content.substring(curr, curr + vari[i].length());
                    //   System.out.println("\t" +temp);
                        if(content.startsWith(vari[i]) == true && content.length() > 2 && content.charAt(content.length() - 2) != ')'&&content.charAt(content.length() - 1) == ';') {
                          //  keyw.add(temp);
                            curr = vari[i].length();
                            String tem = "";
                            while(curr < content.length()) {
                                char c = content.charAt(curr);
                                if(c == '=') {
                                    while(curr < content.length() && c != ',') {
                                        curr++;
                                        System.out.println(c);
                                        c = content.charAt(curr);
                                    }
                                }
                                else if(c == ' '|| c == ','|| c == ';'  ){
                                    if(tem.length() > 0) {
                                  //     System.out.println("variable " + tem);
                                        variable.add(tem);
                                    }
                                    
                                    tem = "";
                                }
                                else {
                                    tem += c;
                                }
                                curr++;
                            }
                           /* if(tem.length() > 0) {
                                  System.out.println(vari[i] + " variable " + tem);
                                  variable.add(tem);
                             }*/
                            
                            flag = 1;
                            break;
                        }
                    }
                }
            content = br.readLine();
            
        }
        
        
        Vector<String> keyw = new Vector<String>();
        Vector<String> delimi = new Vector<String>();
        Vector<String> opera = new Vector<String>();
        Vector<String> speca = new Vector<String>();
        Vector<Character> in = new Vector<Character>();
        Vector<Character> cha = new Vector<Character>();
        Vector<String> id = new Vector<String>();
        f = new FileReader("newfile.c");
        br = new BufferedReader(f);
        content = br.readLine();
        while(content != null) {
          //  System.out.print(content);
            content = content.trim();
            int i,curr;
            char rt = '$';
            if(content.length() > 0) {
                rt = content.charAt(0);
            }
            if(rt == 35) {
                content = br.readLine();
                continue;
                
            }
            
            String s;
            for(curr = 0;curr < content.length();) {
                
                
                char c = content.charAt(curr);
                if(c == 34) {
                   // System.out.println(curr);
                    String tem = "";
                    curr++;
                    while(true) {
                        
                    	c = content.charAt(curr);
                        
                    	if(c == 34) {
                    		if(tem.length() > 0) {
                                    string.add(tem);
                                    System.out.println("(String, \"" + tem + "\")" );
                                    tem = "";
                                }
                            break;
                    	}
                       // System.out.println(c + " p " + tem + " as");
                        if(c == 37) {
                            
                            int flag = 0;
                            for(i = 0;i < spec.length ;i++) {
                                if(curr + spec[i].length() - 1 < content.length()) {

                                    String temp = content.substring(curr, curr + spec[i].length());

                                    if(temp.equals(spec[i]) == true) {
                                        flag = 1;
                                      //  System.out.println("\t" +curr + " " + content + " " + temp);
                                        speca.add(temp);
                                        System.out.println("(specifier, \"" + temp + "\")" );
                                        curr += spec[i].length();
                                        
                                        break;
                                    }
                                }
                            }
                            if( flag == 1) {
                                if(tem.length() > 0) {
                                    string.add(tem);
                                    System.out.println("(String,\" " + tem + "\")" );
                                    tem = "";
                                }
                                continue;
                            }
                            
                            tem += content.charAt(curr);
                            curr++;
                        }
                     
                        tem += c;
                        curr++;
                    }
                    curr++;
                }
               
                int flag = 0;
            //   System.out.println(curr);
                for(i = 0;i < key.length;i++) {
                    if(curr + key[i].length() - 1 < content.length()) {
                        String temp = content.substring(curr, curr + key[i].length());
                    //   System.out.println("\t" +temp);
                        if(temp.equals(key[i]) == true) {
                            
                            keyw.add(temp);
                            System.out.println("(Keyword ,\"" + temp+ "\")"  );
                            curr += key[i].length() ;
                            flag = 1;
                            break;
                        }
                    }
                }
                for(i = 0;i < variable.size()&& flag == 0;i++) {
                    if(curr + variable.get(i).length() - 1 < content.length()) {
                        String temp = content.substring(curr, curr + variable.get(i).length());
                      //  System.out.println("\t" +content + " variable " +temp + " " + variable.get(i));
                        if(temp.equals(variable.get(i)) == true) {
                            id.add(temp);
                            System.out.println("(id ,\"" + temp+ "\")"  );
                            curr += variable.get(i).length() ;
                            flag = 1;
                            break;
                        }
                    }
                }
                for(i = 0;i < delim.length && flag == 0;i++) {
                    if(curr + delim[i].length() -1 < content.length()) {
                        
                        String temp = content.substring(curr, curr + delim[i].length());
                        
                        if(temp.equals(delim[i]) == true) {
                           // System.out.println("\t" +curr + " " + content + " " + temp);
                            delimi.add(temp);
                            System.out.println("(delim ,\"" + temp+ "\")"  );
                            curr += delim[i].length();
                            flag = 1;
                            break;
                        }
                    }
                }
                for(i = 0;i < oper.length && flag == 0;i++) {
                    if(curr + oper[i].length() - 1 < content.length()) {
                        
                        String temp = content.substring(curr, curr + oper[i].length());
                      //  System.out.println("\t" +temp);
                        if(temp.equals(oper[i]) == true) {
                            opera.add(temp);
                            System.out.println("(punct ,\"" + temp + "\")" );
                            curr += oper[i].length();
                            flag = 1;
                            break;
                        }
                    }
                }
                if(flag == 0) {
                    c = content.charAt(curr);
                   // System.out.println(c);
                    if( c >= 48 && c <= 57 ) {
                        String tem = "";
                        while( c >= 48 && c <= 57 ) {
                            
                            tem += c;
                            curr++;
                            c = content.charAt(curr);
                        }
                        System.out.println("(Int ,\"" + tem+ "\")" );
                        curr--;
                        
                    }
                    else if(c >= 97 && c <= 97+ 26){
                        cha.add(c);
                    }
                    curr++;
                }
            }
            
            content = br.readLine();
        }
        int i;
     /*   System.out.print("keyword ");
        for(i = 0;i < keyw.size();i++) {
            System.out.print(   keyw.get(i) + ",");
        }
        System.out.print("\nId ");
        for(i = 0;i < id.size();i++) {
            System.out.print(  id.get(i) + ",");
        }
        System.out.print("\ndelimiter ");
        for(i = 0;i < delimi.size();i++) {
            System.out.print( delimi.get(i) + ",");
        }
        System.out.print("\noperation ");
        for(i = 0;i < opera.size();i++) {
            System.out.print( opera.get(i)+ ",");
        }
        System.out.print("\ninteger ");
        for(i = 0;i < in.size();i++) {
            System.out.print(in.get(i) + ",");
        }
        System.out.print("\ncharacter ");
        for(i = 0;i < cha.size();i++) {
            System.out.print( cha.get(i) + ",");
        }
        System.out.print("\nString ");
        for(i = 0;i < string.size();i++) {
            System.out.print( string.get(i) + ",");
        }
        System.out.print("\nspecifier ");
        for(i = 0;i < speca.size();i++) {
            System.out.print( speca.get(i) + ",");
        }*/
    }
    
}
