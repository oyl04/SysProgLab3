#include <bits/stdc++.h>

using namespace std;

const set<string> keywords = {
            "ALLOCATABLE", "ALLOCATE", "ASSIGN", "ASSOCIATE", "ASYNCHRONOUS",
            "BACKSPACE", "BIND", "BLOCK", "BLOCKDATA", "CALL",
            "CASE", "CHARACTER", "CLASS", "CLOSE", "COMMON",
            "COMPLEX", "CONTAINS", "CONTINUE", "CYCLE", "DATA",
            "DEALLOCATE", "DEFAULT", "DO", "DOUBLE", "ELEMENTAL",
            "ELSE", "ELSEIF", "END", "ENDBLOCK", "ENDBLOCKDATA",
            "ENDDO", "ENDFILE", "ENDFORALL", "ENDFUNCTION", "ENDIF",
            "ENDINTERFACE", "ENDMODULE", "ENDPROGRAM", "ENDSELECT",
            "ENDSUBROUTINE", "ENDTYPE", "ENDWHERE", "ENTRY", "ENUM",
            "EQUIVALENCE", "EXIT", "EXTENDS", "EXTERNAL", "FINAL", "FLUSH",
            "FORALL", "FORMAT", "FUNCTION", "GO", "GOTO",
            "IF", "IMPLICIT", "IMPORT", "INQUIRE", "INTEGER",
            "INTERFACE", "INTRINSIC", "IS", "LOGICAL", "MODULE",
            "NAMELIST", "NON_INTRINSIC", "NON_OVERRIDABLE", "NULLIFY", "ONLY",
            "OPEN", "OPERATOR", "OPTIONAL", "PARAMETER", "PAUSE",
            "POINTER", "PRINT", "PRIVATE", "PROCEDURE", "PROGRAM",
            "PROTECTED", "PUBLIC", "PURE", "READ", "REAL",
            "RECURSIVE", "RESULT", "RETURN", "REWIND", "SAVE",
            "SELECT", "SEQUENCE", "STOP", "SUBROUTINE", "TARGET",
            "THEN", "TYPE", "USE", "VOLATILE", "WAIT",
            "WHERE", "WHILE", "WRITE"
    };
const set <string> operators = {"+", "-", "*", "/", "=", "<", ">", "<=", ">=", "!=", "==", "/=", ".AND.", ".OR.", ".NOT."};
const set <string> separators = {"(", ")", "{", "}", "[", "]", ",", ";"};
const set <string> whitespaces = {" ", "\t", "\n"};

string paint_code(pair<string, string> token) {
    string color;
    if (token.first == "KEYWORD") color = "\033[1;31m";
    else if (token.first == "IDENTIFIER") color = "\033[1;32m";
    else if (token.first == "NUMERIC_LITERAL") color = "\033[1;33m";
    else if (token.first == "OPERATOR") color = "\033[1;34m";
    else if (token.first == "SEPARATOR") color = "\033[1;35m";
    else if (token.first == "COMMENT") color = "\033[1;36m";
    else if (token.first == "UNKNOWN") color = "\033[1;37m";
    else if (token.first == "WHITE_SPACE") color = "\033[1;38m";
    else if (token.first == "STRING_LITERAL") color = "\033[40;97m";
    return color + token.second + "\033[0m";
}
string input;
regex word = regex(R"(^((?:"(?:[^"\\]|\\.)*"|'(?:[^'\\]|\\.)*'))|(<=|>=|!=|==|/=|\+|-|\*|/|=|<|>|\.and\.|\.or\.|\.not\.)|(\(|\)|\{|\}|\[|\]|,|;)|(\d+(?:\.\d+)?)|(\w+)|(\s+))");

vector<pair<string, string>> tokenize() {
        vector<pair<string, string>> tokens;
        vector<string> lines;
        string line;
        for (char c : input) {
            if (c == '\n') {
                line += c;
                lines.push_back(line);
                line = "";
            }
            else line += c;
        }
        if (!line.empty()) lines.push_back(line);
        for (string line : lines) {
            if (line.empty()) continue;
            if (line[0] == '!') {
                tokens.push_back({"COMMENT", line});
                continue;
            }
            smatch match;
            while (regex_search(line, match, word)) {
                string token = match.str();
                if (keywords.find(token) != keywords.end()) tokens.push_back({"KEYWORD", token});
                else if (operators.find(token) != operators.end()) tokens.push_back({"OPERATOR", token});
                else if (separators.find(token) != separators.end()) tokens.push_back({"SEPARATOR", token});
                else if (regex_match(token, regex(R"(\d+(?:\.\d+)?)"))) tokens.push_back({"NUMERIC_LITERAL", token});
                else if (regex_match(token, regex(R"(\w+)"))) tokens.push_back({"IDENTIFIER", token});
                else if (whitespaces.find(token) != whitespaces.end()) tokens.push_back({"WHITE_SPACE", token});
                else if (regex_match(token, regex(R"(["|'].*["|'])"))) tokens.push_back({"STRING_LITERAL", token});
                else tokens.push_back({"UNKNOWN", token});
                line = match.suffix();
            }
        }
        return tokens;
}

int main() {
    string filename;
    FILE* file = fopen("in.txt", "r");
    if (file == NULL) {
        cout << "File not found" << endl;
        return -1;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        input += buffer;
    }
    fclose(file);
    auto tokens = tokenize();
    for (auto token : tokens) cout << paint_code(token);
    return 0;
}
