void TabExtException::constructorCheck(size_t & n, const std::source_location & location){
    if(BYPASS) return;
    try{
        if(n<1){
                TabExtException e(NULL,location, ExceptionType::error, n, n);
                e.constructionFailed();
        }
    }
    catch(TabExtException){
        if(THROW) throw;
        n = 1;
    }
};

void TabExtException::accessCheck(const void* ptr, const std::source_location & location, const size_t & s, const size_t & a, const size_t & i){
    if(BYPASS) return;
    try{
        if ((i<1)||(i>s))
        {
        TabExtException e(ptr, location, ExceptionType::fatal_error, a, s);
        e.accessDenied(i);
        }
    }
    catch(TabExtException){
        if(THROW) throw;
        exit(-1);
    }
};

TabExtException::TabExtException(const void* ptr, const std::source_location & location, const ExceptionType & t, const size_t & s, const size_t & a):Exception(ptr, location, t), size(s), alloc(a){
};

void TabExtException::constructionFailed(){
            message = "Échec de la construction de l'objet TabExt avec les paramètes : \n"; 
            message += " size : " ;
            message += std::to_string(size);
            message += "\n alloc : ";
            message += std::to_string(alloc); 
            message += "\nParamètre corrigé avec la valeur 1.";
            affiche();
            throw *this;
        };

void TabExtException::accessDenied(const size_t & s){
            message = "Echec de l'accès à l'élément ";
            message += std::to_string(s);
            message += " de l'objet TabExt avec les paramètes :  \n";
            message += " size : ";
            message += std::to_string(size);
            message += "\n alloc : ";
            message += std::to_string(alloc);
            message += "\nCe tableau est indicer de 1 jusqu'à sa taille";
            affiche();
            throw *this;
        };
