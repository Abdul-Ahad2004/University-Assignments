#include <iostream>
#include <fstream>
#include <string>
template <typename T>
class XMLData;
using namespace std;
bool global = true;
template <typename T>
class Node 
{
    T data;
    Node<T>* next;

public:
    Node() 
    {
        next = NULL;
    }

    void setdata(T x) 
    {
        data = x;
    }

    T getdata() 
    {
        return data;
    }

    void setnext(Node<T>* n) 
    {
        next = n;
    }

    Node<T>* getnext() 
    {
        return next;
    }
};

template <class T>
class Stack 
{
private:
    Node<T>* head;
    Node<T>* top;
    int size;

public:
    Stack() //constructor
    {
        size = 0;
        head = top = NULL;
    }

    ~Stack() //destructor
    {
        while (!isEmpty()) 
        {
            pop();
        }
    }

    bool isEmpty() //function to check stack is empty
    {
        return size == 0;
    }

    bool push(const T& val) //function to push the element/data into stack
    {
        Node<T>* newNode = new Node<T>();
        newNode->setdata(val);
        newNode->setnext(top);
        top = newNode;
        size++;
        return true;
    }

    T pop()  //function to remove the element/data from top of the stack
    {
        T s;
        if (size == 0) 
        {
            return s;
        }
        Node<T>* temp = top;
        top = top->getnext();
        s = temp->getdata();
        delete temp;
        size--;
        return s;
    }

    T gettop()  //function to get the uppermost data in the stack
    {
        return top->getdata();
    }
};
template<class T>
class XMLData : public Stack<T>
{
public:
    T name;
    T attributes;
    bool isOpeningTag;
    int lineNumber;
    XMLData() //constructor
    {
        isOpeningTag = false;
        lineNumber = -1;
    }
    bool check_attribute(XMLData <T> tag) //function to check attribute contain quotation mark
    {
        int count = 0;
        int len = tag.attributes.length();
        for (int i = 0; i < len; i++)
        {
            int x = int(tag.attributes[i]);
            if (x == 34 || x == 44)
            {
                count++;
            }
        }
        if (count == 0)
            return false;
        else if (count == 1 || count % 2 == 1)
        {
            cout << "Attribute of tag has unmatched quotation at line number " << tag.lineNumber << endl;
            global = false;
            return true;
        }
        else if (count % 2 == 0)
        {
            return true;
        }
        return false;
    }
};
int main() 
{
    int no_of_lines = 0;
    ifstream f1;
    f1.open("input.txt");
    string s;
    while (getline(f1, s)) 
    {
        no_of_lines++; // calculate number of lines in file
    }
    f1.close();
    string* arr = new string[no_of_lines];
    f1.open("input.txt");
    for (int i = 0; i < no_of_lines; i++) 
    {
        getline(f1, arr[i]); //fill the array with file's content
    }
    f1.close();

    Stack< XMLData<string> > stack;
    string s1;
    for (int i = 0; i < no_of_lines; i++) 
    {
        s1 = arr[i];
        int length = s1.length();
        s = "";
        int count = 0;
        for (int j = 0; j < length; j++)
        {
            if (j==0 && s1[j] != '<')
            {
                cout << "Error: There is a no opening tag in line number: " << i + 1 << endl;
                break;
            }
            if (s1[j] == '<')
                count = 0;
            if (count == 0 && s1[j] != '>')
            {
                s += s1[j];
            }
            else
            {
                count = 1;
                s += s1[j];
                int length1 = s.length();
                if (i == 0 && s.find("<?") == -1)
                {
                    cout << "Error: XML prolog(header) is missing" << endl;
                    global = false;
                }
                // Handle XML prolog
                if (s.find("<?") != -1) 
                {
                    if (s[length1 - 1] == '>' && s[length - 2] == '?') 
                    {
                        XMLData<string> tag;
                        tag.name = s.substr(1, s.find('>') - 1);
                        tag.isOpeningTag = true;
                        tag.lineNumber = i + 1;

                        // Get the attributes of the tag.
                        int start = tag.name.find(' ');
                        if (start != -1)
                            start++;
                        int end = tag.name.length();

                        if (start != -1 && end != -1) {
                            tag.attributes = tag.name.substr(start, end - start);
                        }
                        if (tag.attributes != "")
                        {
                            bool check = tag.check_attribute(tag);
                            if (!check)
                            {
                                global = false;
                                cout << "Error: Attribute does not has any quotation at line number " << tag.lineNumber << endl;
                            }
                        }
                        continue;
                    }
                    else
                    {
                        global = false;
                        cout << "Error : Unmatched closing XML prolog(header) tag at line no: " << i + 1 << endl;
                    }
                }
                // Handle XML comments
                if (s[0] == '<' && s[1] == '!')
                {
                    if (s[2] == '-' && s[3] == '-' && s[length1 - 1] == '>' && s[length - 2] == '-' && s[length - 3] == '-')
                    {
                        continue;
                    }
                    else
                    {
                        global = false;
                        cout << "Error : Unmatched closing XML comment tag at line no: " << i + 1 << endl;
                    }
                }

                // If the line contains an opening tag, push it into the stack.
                else if (s[0] == '<' && s[1] != '/') 
                {
                    XMLData<string> tag;
                    tag.name = s.substr(1, s.find('>') - 1);
                    tag.isOpeningTag = true;
                    tag.lineNumber = i + 1;

                    // Get the attributes of the tag.
                    int start = tag.name.find(' ');
                    if (start != -1)
                        start++;
                    int end = tag.name.length();

                    if (start != -1 && end != -1) {
                        tag.attributes = tag.name.substr(start, end - start);
                    }
                    if (tag.attributes != "")
                    {
                        bool check = tag.check_attribute(tag);
                        if (!check)
                        {
                            global = false;
                            cout << "Error: Attribute does not has any quotation at line number " << tag.lineNumber << endl;
                        }
                    }

                    stack.push(tag);
                }

                // If the line contains a closing tag
                else if (s[0] == '<' && s[1] == '/') 
                {
                    string name;
                    // If the stack is empty, then the closing tag is unmatched.
                    if (stack.isEmpty()) 
                    {
                        global = false;
                        cout << "Error: Unmatched closing tag at line " << i + 1 << endl;
                        break;
                        
                    }
                    // Pop the top tag from the stack for compare 
                    XMLData<string> tag = stack.pop();
                    name = tag.name.substr(0, tag.name.find(' '));
                    if (name != s.substr(2, s.find('>') - 2)) 
                    {
                        string name1;
                        int counter = 0;
                        XMLData<string> tag1 = stack.pop();
                        name1 = tag1.name.substr(0, tag1.name.find(' '));
                        if (name1 == s.substr(2, s.find('>') - 2))
                        {
                            counter++;
                            cout << "Error: Mismatched tag \'" << name << "\' at line number " << tag.lineNumber << endl;
                            global = false;

                        }
                        if (counter == 0)
                        {
                            stack.push(tag1);
                            // If the tags do not match, then error
                            cout << "Error: Mismatched tag \'" << name << "\' at line number " << tag.lineNumber << endl;
                            global = false;
                        }
                    }

                    // Check if the attributes of the opening and closing tags match.
                    int start = s.find(' ') + 1;
                    int end = s.find('>', start);
                    if (start != -1 && end != -1) 
                    {
                        string closingAttributes = s.substr(start, end - start);
                        if (tag.attributes != "" && closingAttributes == "") 
                        {
                            global = false;
                            cout << "Error: Mismatched attributes at lines " << tag.lineNumber << " and " << i + 1 << endl;

                        }
                    }
                }
                s = "";
            }
        }
    }
    // If the stack is not empty, then there are unmatched opening tags.
    if (!stack.isEmpty()) 
    {
        cout << "There are unmatched opening tags in the XML file." << endl;

        // Pop all the tags from the stack and print them to the console.
        while (!stack.isEmpty()) 
        {
            XMLData<string> tag = stack.pop();
            global = false;
            cout << "Unmatched tag: " << tag.name << ", line number: " << tag.lineNumber << endl;
        }
    }
    else 
    {
        if (global)
        {
            cout << "All the tags in the XML file are matched." << endl;
        }
    }
    delete[]arr;
    arr = NULL;
    return 0;
}

