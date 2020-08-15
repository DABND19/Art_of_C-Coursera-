#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person {
public:
    Person() {}
    explicit Person(const string& name, const string& profession) :
    name(name),
    profession(profession)
    {}
    virtual string Name() const {
        return name;
    }
    virtual string Profession() const {
        return profession;
    }
    virtual void Walk(const string& destination) const {
        PrintPerson();
        cout << " walks to: " << destination << endl;
    }
    void VisitPlaces(const vector<string>& places) {
        for (const auto& place : places) {
            Walk(place);
        }
    }
    void PrintPerson() const {
        cout << Profession() << ": " << Name();
    }
private:
    const string name;
    const string profession;
};

class Student : public Person {
public:
    Student() {}
    explicit Student(const string& name, const string& favourite_song) :
    Person(name, "Student"),
    favourite_song(favourite_song)
    {}
    string FavouriteSong() const {
        return favourite_song;
    }
    void Learn() const {
        PrintPerson();
        cout <<  " learns" << endl;
    }
    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }
    void SingSong() const {
        PrintPerson();
        cout << " sings a song: " << FavouriteSong() << endl;
    }
private:
    const string favourite_song;
};

class Teacher : public Person {
public:
    Teacher() {}
    explicit Teacher(const string& name, const string& subject) :
    Person(name, "Teacher"),
    subject(subject)
    {}
    string Subject() const {
        return subject;
    }
    void Teach() const {
        PrintPerson();
        cout << " teaches: " << Subject() << endl;
    }
private:
    const string subject;
};

class Policeman : public Person {
public:
    Policeman() {}
    explicit Policeman(const string& name) :
    Person(name, "Policeman")
    {}
    void Check(const Person& person) {
        PrintPerson();
        cout << " checks " << person.Profession() << ". "
        << person.Profession() << "'s name is: " << person.Name() << endl;
    }
};

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    t.VisitPlaces({"Moscow", "London"});
    p.Check(s);
    s.VisitPlaces({"Moscow", "London"});
    return 0;
}