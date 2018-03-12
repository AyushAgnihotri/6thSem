
package codtokenizer;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;

public class CODTokenizer {

    public static void main(String[] args) throws Exception {
        ArrayList<String> keywords = new ArrayList<>();
        ArrayList<String> delimeters = new ArrayList<>();
        ArrayList<String> punct = new ArrayList<>();
        ArrayList<Token> symbolTable = new ArrayList<>();
        int isComment = 0;    // Used as flags for uncommenting
        int idCount = 1;

        // Adding keywords
        BufferedReader br = new BufferedReader(new FileReader("keywords.txt"));
        String line;

        while ((line = br.readLine()) != null) {
            keywords.add(line.trim());
        }

        br.close();

        // adding delimeters
        br = new BufferedReader(new FileReader("delimeters.txt"));

        while ((line = br.readLine()) != null) {
            delimeters.add(line.trim());
        }

        // Adding punct
        br = new BufferedReader(new FileReader("punct.txt"));

        while ((line = br.readLine()) != null) {
            punct.add(line.trim());
        }

        br.close();

        // Reading code
        br = new BufferedReader(new FileReader("hello.c"));
        
        FileInputLoop:
        while ((line = br.readLine()) != null) {
            /* ===== ===== ===== Uncommenting Code ===== ===== ===== */
            String[] y = line.split("[\\s,{}();]+");
            int l = y.length;
            int multiCommentIndex = 0;
            //System.out.println(line);
            for (int i = 0; i < l; i++) {
                String s = y[i];
                if (s.startsWith("//")) {   // End of line comment
                    continue FileInputLoop;
                } else if (s.startsWith("/*")) {    // Beginning of Regular comment
                    isComment = 1;
                } else if (s.endsWith("*/")) {      // Closing of Regular comment
                    isComment = 0;
                    multiCommentIndex = line.indexOf(s) + 2;
                }
            }

            /* ===== ===== ===== End of Uncommenting Code ===== ===== ===== */
            // Checking flags of uncommenting code
            if (isComment == 1) {
                continue;
            }
            
            String str = line.substring(multiCommentIndex);

            for (int i = 0; i < str.length(); ++i) {
                //System.out.println("charAt(" + i + ") = " + str.charAt(i));

                if (str.charAt(i) == ' ' || str.charAt(i) == '\t') {
                    // skip
                    //System.out.println("case 1");
                } else if (str.charAt(i) == '"') {
                    //System.out.println("case 2");
                    int index = i + 1;

                    while (str.charAt(index) != '"') {
                        ++index;
                    }

                    String word = str.substring(i + 1, index);

                    i = index;
                    symbolTable.add(new Token("id" + idCount, word));
                } else if (punct.contains(Character.toString(str.charAt(i)))) {
                    symbolTable.add(new Token("punct", Character.toString(str.charAt(i))));
                } else if (delimeters.contains(Character.toString(str.charAt(i)))) {
                    //System.out.println("case 3");
                    symbolTable.add(new Token("delim", Character.toString(str.charAt(i))));
                } else if (str.charAt(i) >= '0' && str.charAt(i) <= '9') {
                    int fromIndex = i;
                    ++i;

                    while (isNumber(str.charAt(i))) {
                        ++i;
                    }

                    String word = str.substring(fromIndex, i);

                    if (isNumberValue(word) == 1) {
                        symbolTable.add(new Token("int", word));
                    } else {
                        symbolTable.add(new Token("float", word));
                    }
                    --i;
                } else {
                    //System.out.println("case 4");
                    int index = i;

                    for (int j = i; j < str.length(); ++j) {
                        index = j;

                        if (!(isIdentifier(str.charAt(j)) || isFileName(str.charAt(j)) || isNumber(str.charAt(j)))) {
                            break;
                        }
                    }

                    String word = str.substring(i, index);

                    if (word.length() != 0) {
                        if (keywords.contains(word)) {
                            //System.out.println("case 4-1");
                            symbolTable.add(new Token("keyword", word));
                        } else if (isNumberValue(line) != 0) {
                            if (isNumberValue(line) == 1) {
                                symbolTable.add(new Token("int", word));
                            } else {
                                symbolTable.add(new Token("float", word));
                            }
                        } else {
                            //.out.println("case 4-2");
                            symbolTable.add(new Token("id" + idCount, word));
                            ++idCount;
                        }
                    }

                    //System.out.println("index(" + index + ")  = " + str.charAt(index));
                    i = index - 1;
                }
            }
        }

        // printing tokens
        for (Token t : symbolTable) {
            System.out.println(t.toString());
        }
    }

    public static boolean isIdentifier(char value) {
        return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z') || (value >= '0' && value <= '9');
    }

    public static boolean isFileName(char value) {
        return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z') || (value >= '0' && value <= '9') || (value == '.');
    }

    public static boolean isNumber(char value) {
        return (value >= '0' && value <= '9') || (value == '.');
    }

    public static int isNumberValue(String value) {
        boolean result = true;
        boolean isFloat = false;

        for (int i = 0; i < value.length(); ++i) {
            if (value.charAt(i) == '.') {
                isFloat = true;
            }

            if (!isNumber(value.charAt(i))) {
                result = false;
                break;
            }
        }

        if (result) {
            if (isFloat) {
                return 2;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    }

    public static void uncommentFile(String filename) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader(filename));
        String finalText = "";
        String line;

        while ((line = br.readLine()) != null) {
            if (line.contains("//")) {
                int commentIndex = line.indexOf("//");
                int quoteFromIndex = line.indexOf("\"");
                int quoteToIndex = line.indexOf("\"");

                if (quoteFromIndex == -1) {
                    finalText += line.substring(0, commentIndex) + "\n";
                } else if (quoteToIndex < commentIndex) {
                    finalText += line.substring(0, commentIndex) + "\n";
                }
            } else if (line.contains("/*")) {
                int commentIndex = line.indexOf("//");
                int quoteFromIndex = line.indexOf("\"");
                int quoteToIndex = line.indexOf("\"");

                if (quoteFromIndex != -1) {
                    if (quoteToIndex < commentIndex) {
                        finalText += line.substring(0, commentIndex) + "\n";
                    }
                }
            }
        }
    }
}

class Token {

    public String category, text;

    public Token(String category, String text) {
        this.category = category;
        this.text = text;
    }

    @Override
    public String toString() {
        return "(" + category + ", \"" + text + "\")";
    }
}
