#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <sys/mman.h>
#include <map>
#include <string>

const int INT_MIN = -2147483647;
const int INT_MAX = 2147483647;

// Assuming the required types and enums are defined
enum Variable {
    VAR_X = 0 // Define your variable constants here
};

// Base struct for an AST Node
struct ASTNode {
    std::vector<std::unique_ptr<ASTNode>> children; // Child nodes
    ASTNode() {}
};

// Derived struct for a Switch statement
struct TableSwitchNode : ASTNode {
    int offset_default;
    std::unordered_map<int, int> caseMap;
    int low_val;
    int high_val;
    TableSwitchNode() : ASTNode(ASTNodeType::Switch) {}
};

// Derived struct for a Case statement
struct CaseNode : ASTNode {
    int caseValue; // Case value specific to CaseNode

    CaseNode(int value) : ASTNode(ASTNodeType::Case), caseValue(value) {}
};

// Derived struct for a Default case statement
struct DefaultNode : ASTNode {
    DefaultNode() : ASTNode(ASTNodeType::Default) {}
};

// Derived struct for Goto statements
struct GotoNode : ASTNode {
    std::string label; // Label specific to GotoNode

    GotoNode(const std::string& lbl) : ASTNode(ASTNodeType::Goto), label(lbl) {}
};

// Placeholder for JITFunction
using JITFunction = void(*)(); // Function pointer type for JIT compiled function

class JITCompiler {
public:
    JITCompiler(const std::map<int, int>& env) : env(env) {}

    static void compile_x86_64(std::vector<std::string>& assembly, ASTNode* tree) {
        for (const auto& node : tree) {
            if (line.find(":") != std::string::npos) {
                size_t colonIndex = line.find(":");
                std::string caseStr = line.substr(0, colonIndex);
                int label = std::stoi(line.substr(colonIndex+1));
                if !caseStr.compare("default") {
                    tableswitch->offset_default = label;
                } else {
                    int caseValue = std::stoi(caseStr); // Convert case label to int
                    tableswitch->caseMap[caseValue] = label;
                    if caseValue < min {
                        min = caseValue;
                    } 
                    if caseValue > max {
                        max = caseValue;
                    }
                }

            } else {
                break; //No more labels
            }
        }
    }

    JITFunction compile_jvm_function(ASTNode* tree) {
        std::vector<std::uint8_t> assembly;
        assembly.clear();

        // Allocate executable memory
        auto memory = static_cast<uint8_t*>(mmap(nullptr, 1024,
                                                  PROT_READ | PROT_WRITE | PROT_EXEC,
                                                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
        if (memory == MAP_FAILED) {
            throw std::runtime_error{"Cannot allocate memory"};
        }

        // Assembly instructions
        // push rbp
        assembly.push_back(0x55);
        // mov rbp, rsp (REX.W + 89 /r)
        assembly.push_back(0x48); // REX
        assembly.push_back(0x89); // opcode
        assembly.push_back(0xe5); // ModR/M byte (mov rsp, rbp)

        
        compile_x86_64(assembly, tree);

        // Add a return instruction (RET)
        assembly.push_back(0xc3); // RET

        // Copy assembly to the allocated memory
        std::memcpy(memory, assembly.data(), assembly.size());

        // Cast the memory to the function pointer type
        return reinterpret_cast<JITFunction>(memory);
    }

    void dump_assembly() {
        // Implement assembly dumping for debugging if needed
        std::cout << "Dumping assembly code (in hex):\n";
        // Implement a way to print the assembly instructions in hex
    }

private:
    const std::map<int, int>& env;
};

// Placeholder for the JVMParser class
class JVMParser {
    public:

    static void handle_tableswitch(ASTNode* tree, const std::vector<std::string>& bytecode) {
        ASTNode* tableswitch = new TableSwitchNode();
        tree->children.push_back(tableswitch);
        int min = INT_MIN;
        int max = INT_MAX;
        for (contst auto& line : bytecode) {
            if (line.find(":") != std::string::npos) {
                size_t colonIndex = line.find(":");
                std::string caseStr = line.substr(0, colonIndex);
                int label = std::stoi(line.substr(colonIndex+1));
                if !caseStr.compare("default") {
                    tableswitch->offset_default = label;
                } else {
                    int caseValue = std::stoi(caseStr); // Convert case label to int
                    tableswitch->caseMap[caseValue] = label;
                    if caseValue < min {
                        min = caseValue;
                    } 
                    if caseValue > max {
                        max = caseValue;
                    }
                }

            } else {
                break; //No more labels
            }
        }
    }

    static ASTNode* parse_from_bytecode(const std::vector<std::string>& bytecode) {
        ASTNode* root = new ASTNode(); // Create a root switch node

        for (const auto& line : bytecode) {
            if (line.find("tableswitch") != std::string::npos) {
                handle_tableswitch(root, bytecode);
            }  
            else if (line.find("return") != std::string::npos) {
                // Handle return statement
                ASTNode* returnNode = new ASTNode(ASTNodeType::Return);
                root->children.push_back(returnNode); // Add it to the root
            }
        }

        return root; // Return the constructed AST
    }
};

// Placeholder for the JVMInterpreter class
class JVMInterpreter {
public:
    JVMInterpreter(const std::map<int, int>& env) : env(env) {}

private:
    const std::map<int, int>& env;
};

int main() {
    auto env = std::map<int, int>{{VAR_X, 3}};

    auto stupidSwitch = std::vector<std::string> {
        "0: iconst_1",
        "1: istore_1",
        "2: iload_1",
        "3: tableswitch {"
        "    2: 28"
        "    3: 31"
        "    4: 34"
        "    default: 37"
        "}",
        "28: goto 37",
        "31: goto 37",
        "34: goto 37",
        "37: return"
    };

    JITCompiler jit_compiler(env);
    JVMInterpreter jvm_interpreter(env);

    // Parse the bytecode into an AST
    ASTNode* tree = JVMParser::parse_from_bytecode(stupidSwitch);
    
    // Compile the function
    JITFunction fun = jit_compiler.compile_jvm_function(tree);

    // Optional: Dump the assembly for debugging
    jit_compiler.dump_assembly();

    // Execute the compiled function
    fun();

    // Clean up (if necessary)
    munmap(tree, sizeof(ASTNode)); // Assuming tree is dynamically allocated
    return 0;
}