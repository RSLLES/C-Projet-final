#ifndef DATE
#define DATE

class Date{
    /* Classe représentant une date.
    Elle se base sur la blibliothèque Ctime du C, en l'adaptant pour que celle ci soit plus pratique.
    Une date est créée avec un jour, un mois et une année. Chacun peut petre modifié indépendament.
    La date est prise localement sur la machine.

    Le constructeur donne par défaut comme valeur à la date celle du jour ou elle est crée.
    */

   protected:
    int year;
    int month;
    int day;

   public:
    Date(int _day, int _month, int _year);
    Date();
    void Print();

    int GetDay();
    int GetMonth();
    int GetYear();

    void SetDay(int);
    void SetMonth(int);
    void SetYear(int);
};

#endif