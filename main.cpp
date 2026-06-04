#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//=======================
//Base Class (Inheritance)
//=======================
class User {
	protected:
		string name;
		int age;
		
	public:
		User(string n = "", int a = 0) {
			name = n;
				age =a;
		}
		virtual void displayProfile() = 0; //polymorphism
		
		string getName () {
			return name;
		}
};
//============================
//Derived Class
//============================
class Student : public User {
	private:
		vector <string> skills;
		
		public:
			Student(string n, int a) : User(n,a) {}
			
			void addSkill(string skill){
				skills.push_back(skill);
			}
			vector<string> getSkills(){
				return skills;
			}
			
			int getAge(){
				return age;
			}
			
			void displayProfile() override {
			cout <<"\n===== STUDENT PROFILE=====\n";
			cout <<"Name: " << name << endl;
			cout <<"Age: " << age << endl;
			cout <<"Skills: "; 
			
			for (int i=0; i < skills.size(); i++){
				cout << skills[i];
				if(i < skills.size() - 1){
					cout << ", ";
				}
			}
			cout << endl;
					}
};
//============================
//Career Class
//============================
class Career {
	private:
		string careerName;
		vector<string> requiredSkills;
		
		public:
			Career(string name, vector<string>skills){
				careerName = name;
				requiredSkills = skills;
			}
			
			string getCareerName(){
				return careerName;
			}
			
			int calculateScore(vector<string>userSkills){
				int score = 0;
				
				for (string us : userSkills) {
					for (string rs :requiredSkills){
						if (us==rs)
						score += 10;
					}
				}
				return score;
			}
};
//============================
//Recommendation Engine
//============================
class RecommendationEngine {
	private:
		vector<Career> careers;
		
		public:
			void loadCareers(){
				
				careers.push_back(Career("Software Engineer", {"Programming","ProblemSolving","Coding","Database","Networking"}));
			
			careers.push_back(Career("Data Scientist", {"Programming","Statistics","Coding","MachineLearning","Analytics"}));
			
			careers.push_back(Career("Cyber Security Analyst", {"Networking","Security","ProblemSolving"}));
			
			careers.push_back(Career("Project Manager" , {"Organisation","Time Management","Coordination"}));
			
			careers.push_back(Career("Banker", {"Communication","Money Management","Budgeting"}));
			
			careers.push_back(Career("Architect", {"Spatial thinking","Creativity","Drawing","Mathematics","Physics"}));
			
			careers.push_back(Career("Graphic Designer", {"Creativity","Photoshop","Design"}));
			
			careers.push_back(Career("Civil Engineer", {"Mathematics","Physics","Design"}));
						}
						void recommend(Student & student){
							vector<string> skills = student.getSkills();
								
								int bestScore = -1;
								string bestCareer;
								
								cout <<"\n===== CAREER SCORES=====\n";
								
								for (Career c: careers){
									int score = c.calculateScore(skills);
									
									cout << c.getCareerName()
									     <<" --> Score: "
									     << score 
										 << " points"
										 << endl;
									     
									     if (score > bestScore) {
									     	bestScore = score;
									     	bestCareer = c.getCareerName();
										 }
								}
								
							   	cout << "\nRecommended Career: "
								     << bestCareer <<endl;
						}
};
//============================
//File Handling
//============================
class FileManager {
	public:
	    static void saveStudent(Student & student)
	{
		
		ofstream file("students.txt",ios::app);
		
		if (file.is_open()) {
			file << student.getName() << "," << student.getAge() << ",";
			vector<string> skills = student.getSkills();
			for(int i=0; i< skills.size(); i++){
				file<< skills[i];
				if(i< skills.size()-1) file << ",";
			}
		    file <<	endl;
				file.close();
		}
	}
};
//============================
//Main Program
//============================
int main(){
	string name;
	int age;
	int n;
	
	cout << "===== CAREER PATH RECOMMENDATION SYSTEM =====\n";
	
	cout << "Enter Name: ";
	getline(cin, name);
	
	cout << "Enter Age: ";
	cin >> age;
	
	Student student(name, age);
	
	cout << "How many skills do you have? ";
	cin >>n;
	
	cin.ignore();
	
	for (int i=0; i<n; i++){
		string skill;
		
		cout << "Enter Skill"
		     << i + 1 << ":";
		     
		     getline(cin, skill);
		     
		     student.addSkill(skill);
	}
	
	student.displayProfile();
	
	RecommendationEngine engine;
	engine.loadCareers();
	
	engine.recommend(student);
	FileManager::saveStudent(student);
	
	cout << "\nData saved successfully.\n";
	
	return 0;
		}