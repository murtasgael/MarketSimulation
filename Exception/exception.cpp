using namespace std;

//Intialisaétion des membres statiques
bool Exception::BYPASS = false;
bool Exception::THROW = false;
//string path = "../LOG";

Exception::Exception(const void* ptr, const std::source_location & lc, const ExceptionType & t): obj(ptr), location(lc), type(t) {
}

void Exception::affiche(){
    cout << "\n- - - - - - - - - -" << endl;
    string s = " WARNING ";
    switch (type){
        case (ExceptionType::error) :
            s = " ERROR ";
        break;
        case (ExceptionType::fatal_error) :
            s = " FATAL_ERROR ";
    }
    cout << s << endl;
    cout << "- - - - - - - - - -" << endl;
    cout << "fichier : " << location.file_name() << endl;
    cout << "fonction : " << location.function_name() << endl;
    cout << "ligne : " << location.line() << endl;
    if(obj) cout << "adresse de l’object : " << &obj << endl;
    cout << "- - - - - - - - - -" << endl;
    cout << message << endl;
    cout << "- - - - - - - - - -" << endl;
}

