#include <iostream>
#include <vector>
#include <memory>
#include <random>

template<class T>
class Worker {
public:

	typedef std::shared_ptr<Worker<T>> SharedWorker;

	bool Initialize() {
		std::cout <<"Initialize:Worker:"<< V << std::endl;
		return true;
	}

	T GetValue() const{
		return V;
	}
	bool SetValue(const T& In) {
		std::cout << "SetValue:" << V << " -> " << In << std::endl;
		V = In;
		return true;
	}
	bool Work() {
		std::cout << "Work:" << V<<" -> "<<V+1 << std::endl;
		V++;
		return true;
	}
	bool Eat() {
		std::cout << "Eat:" << V << std::endl;
		return true;
	}
	bool Leave() {
		std::cout << "Leave:" << V << std::endl;
		return true;
	}
	bool Otingin(const T& ti) {
		std::cout << "Bonus:" <<O+ti << std::endl;
		O += ti;
		return true;
	}

protected:
	T V=std::random_device()();
	T O = 0;
};

class TestSystem {
public:
	typedef unsigned int Value;

	bool Initalize() {
		std::cout << "Initialize:System" << std::endl;
		W.clear();
		V.clear();
		return true;
	}
	bool Push(Worker<Value>::SharedWorker In) {
		V.push_back(In->GetValue());
		W.push_back(In);
		W.back()->Initialize();
		return true;
	}
	bool Work() {
		for (auto& o : W) {
			o->Work();
		}
		return true;
	}

	bool Eat() {
		for (auto& o : W) {
			o->Eat();
		}
		return true;
	}

	bool Leave() {
		for (auto& o : W) {
			o->Otingin(std::random_device()()%100);
			o->Leave();
		}
		return true;
	}
	bool ReStore() {
		std::cout << "Start Restore!" << std::endl;
		for (std::size_t i = 0; i < W.size(); i++) {
			W[i]->SetValue(V[i]);
		}
		return true;
	}
	~TestSystem() {
		std::cout << std::endl << "Start Destruction." << std::endl << std::endl;
		ReStore();
		Leave();
		Initalize();
	}
protected:

	std::vector<Worker<Value>::SharedWorker> W;
	std::vector<Value> V;
	//Value Ot = 100;
};

typedef Worker<TestSystem::Value> IntWorker;

int main() {
	IntWorker::SharedWorker A = std::make_shared<IntWorker>();
	IntWorker::SharedWorker B = std::make_shared<IntWorker>();
	IntWorker::SharedWorker C = std::make_shared<IntWorker>();
	IntWorker::SharedWorker D = std::make_shared<IntWorker>();
	{
		TestSystem TS;

		std::cout << "Welcome to TestSystem." << std::endl << std::endl;

		std::cout << "Start Initialize!" << std::endl << std::endl;
		TS.Initalize();
		std::cout << std::endl << "Add Worker." << std::endl;
		TS.Push(A);
		TS.Push(B);
		TS.Push(C);
		TS.Push(D);
		for (std::size_t j = 0; j < 7; j++) {
			std::cout << std::endl << "Start a day." << std::endl << std::endl;
			for (std::size_t i = 0; i < 3; i++) {
				std::cout << "Eat One!" << std::endl;
				TS.Eat();
				std::cout << std::endl;
				std::cout<< "Work One!" << std::endl;
				TS.Work();
				std::cout << std::endl;
			}
			std::cout << "End a day." << std::endl << std::endl;
			TS.Leave();
		}
	}

	return 0;
}