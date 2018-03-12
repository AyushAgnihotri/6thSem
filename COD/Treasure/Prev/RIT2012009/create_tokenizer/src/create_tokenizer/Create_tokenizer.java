/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package create_tokenizer;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

/**
 *
 * @author Aturag
 */
public class Create_tokenizer {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        FileReader f;
        int cur;
        comment_removal object1 = new comment_removal();
        object1.read();
       /* f = new FileReader("newfile.c");
        BufferedReader br = new BufferedReader(f);
      /*  cur = br.read();
        while(cur != -1) {
            System.out.print((char)cur);
            cur = br.read();
        }*/
        token_token object2 = new token_token();
        object2.make_token();
    }
    
}
