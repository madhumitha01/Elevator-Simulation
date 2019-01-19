#include<iostream>
#include<fstream>
using namespace std;

class LiftRequest {
public:
    int dest;
    int src;
    int ppl;
    void toString() {
        cout<<"LIFT REQUEST -> SOURCE: "<<src<<" DESTINATION: "<<dest<<" PPL: "<<ppl<<endl;
        cout<<endl;
    }
};

class Lift {
public:
    LiftRequest lr;
    Lift() {
        lr.src=0;
        lr.dest=0;
        lr.ppl=0;
    }
    void process(int id) {
    cout<<endl<<" ############## Moving Lift "<<(id+1)<<" FROM "<<lr.src<<" TO "<<lr.dest<<" ############## "<<endl;
        lr.src=lr.dest;
        lr.ppl=0;
    }
    friend void toString(int, Lift);
};
void toString(int id, Lift l) {
    cout<<"LIFT "<<(id+1)<<(l.lr.src==l.lr.dest?" @ REST":"LIFT @ MOVING")<<" SOURCE:"<<l.lr.src<<" DESTINATION:"<<l.lr.dest<<" PPL:"<<l.lr.ppl<<endl;
}

class LiftHandler {
public:
    Lift l[4];
    void showLiftStatus() {
        cout<<"------------------------------------------------"<<endl;
        cout<<"ALL LIFT STATUS"<<endl;
        cout<<"------------------------------------------------"<<endl;
        for(int j=0;j<4;j++) {
            toString(j, l[j]);
        }
        cout<<"------------------------------------------------"<<endl;
        cout<<endl;
    }
    void process(LiftRequest lr) {
        cout<<"**************************************************"<<endl;
        cout<<"BEFORE"<<endl;
        showLiftStatus();
        cout<<"PROCESSING LIFT REQUEST........."<<endl;
        lr.toString();
        int found = 0;
        do {
            for(int i=0;i<4;i++) {
                // IF IN REST and DESTINATION
                if(lr.src==l[i].lr.dest) {
                    found = 1;
                    l[i].lr = lr;
                    l[i].process(i);
                    break;
                }
            }
        
            if(!found) {
                cout<<"NO LIFT FOUND"<<endl<<"GETTING LIFT TO "<<lr.src<<endl;
                l[0].lr.src = lr.src;
                l[0].lr.dest = l[0].lr.src;
                l[0].lr.ppl=0;
                toString(0, l[0]);
            }
        } while(!found);
        cout<<endl<<"AFTER"<<endl;
        showLiftStatus();
        cout<<"**************************************************"<<endl;
    }
};

// File Handler Protocol
class FileHandler {
public:
    virtual void readFromFile()=0;
    virtual void writeToFile(LiftRequest)=0;
};

class MyFileHandler:public FileHandler {
private:
    LiftHandler lh;
public:
    void readFromFile();
    void writeToFile(LiftRequest);
};
void MyFileHandler::writeToFile(LiftRequest lf) {
    ofstream outfile;
    outfile.open("LftRe.txt", ios::app);
    outfile<<lf.dest<<" "<<lf.src<<" "<<lf.ppl<<endl;
    outfile.close();
}
void MyFileHandler::readFromFile() {
    char wait;
    ifstream infile;
    infile.open("LftRe.txt");
    while(!infile.eof()) {
        LiftRequest lf;
        infile>>lf.src;
        infile>>lf.dest;
        infile>>lf.ppl;
        cout<<"New Lift Request"<<endl;
        lf.toString();
        if(lf.ppl<8) {
            lh.process(lf);
        } else {
            cout<<"NO OF PPL LIMIT EXCEEDED"<<endl;
        }
        cout<<"Press any key to continue..."<<endl;
        cin>>wait;
    }
}
int main() {
    MyFileHandler fh;
    fh.readFromFile();
    //test();
    int ij;
    cin>>ij;
    return 0;
}

