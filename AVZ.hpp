#ifndef _AVZ_
#include<list>
#include<string>
#include<algorithm>
#include<cctype>

namespace avz
{
	class StoryCharacter;
	class Zombie;
	class Alien;
	class Health;
	class Arrow;
	class Rock;
	class Gameboard;
	class Control;
	
	class Object
	{
		public:
			Object();
			virtual ~Object();
			void setSymbol(const char c);
			char getSymbol() const;
			virtual void show() const;
			int getX();
			int getY();
			void setX(const int _x);
			void setY(const int _y);
			virtual Object& reveal();
			virtual void encounterEvent(Alien& alien);
			void setControl(Control* ptr);
		protected:
			int x;
			int y;
			char symbol;
			Control* control;
	};
	
	class StoryCharacter : public Object
	{
		public:
			//StoryCharacter();
			//~StoryCharacter();
			StoryCharacter(Gameboard&);
			virtual void move(const int, const int);
			virtual void attack(StoryCharacter&);
			virtual int attacked(const int damage);
			virtual void collect(const Health&);
			virtual void collect(const Arrow&);
			
			//virtual void encounter(Object&);
			int getLife();
			void setLife(const int life);
			int getAttackPower();
			void setAttackPower(const int attackPower);
			int getMaxLife() const;
			void setMaxLife(const int _maxLife);
			int getMaxAttackPower() const;
			void setMaxAttackPower(const int _maxAttackPower);
			void setNextTranslationX(int x);
			void setNextTranslationY(int y);
			int getNextTranslationX() const;
			int getNextTranslationY() const;
			
		protected:
			Gameboard& gameboard;
			int life;
			int attackPower;
			int maxLife;
			int maxAttackPower;
			int nextTranslationX;
			int nextTranslationY;
			
		
		
	};
	
	
	
	class Gameboard
	{
		public:
			Gameboard();
			Gameboard(const int rowCount, const int columnCount);
			~Gameboard();
			Object& getObjectAt(const int x, const int y);
			void setObjectAt(Object&, const int x, const int y);
			void show() const;
			void refreshAllTrail();
			void placeAlien(Alien&, const int x, const int y);
			int getRowCount();
			int getColumnCount();
			int getZombieCount() const;
			void setZombieCount(int count);
			Zombie& getZombie(const int index);
			void setControl(Control* ptr);
		private:
			int rowCount;
			int columnCount;
			int zombieCount;
			//Object** map;
			std::list<std::list<Object*> > objects;
			std::list<Zombie*> zombies;
			void randFill();
			void randFillZombie();
			Control* control;
			
		
	};
	
	class Alien : public StoryCharacter
	{
		public:
			//Alien();
			Alien(Gameboard&);
			Object& yields();
			virtual void move(const int, const int);
			virtual void attack(StoryCharacter&);
			virtual void attack(Zombie&);
			virtual void collect(const Health&);
			virtual void collect(const Arrow&);
			virtual void collect(Rock&);
			virtual void stop();
			virtual void readyToGo();
			virtual bool isReadyToMove();
			virtual int calculateNextStep(const int nextTranslation);
			~Alien();
		protected:
			int stopStatus;
		private:
	};
	
	class Zombie : public StoryCharacter
	{
		public:
			//Zombie();
			Zombie(Gameboard&);
			Zombie(Gameboard& gb, const char ch);
			Zombie(Gameboard& gb, const char ch, const int life, const int attack_power, const int attack_range);
			//virtual ~Zombie();
			void setAttackRange(int);
			int getAttackRange() const;
			virtual void encounterEvent(Alien& alien);
		protected:
		private:
			int attackRange;
	};
	
	class Control
	{
		public:
			Control(Gameboard&, Alien&);
			~Control();
			int work();
			void display();
			void setStatusTxt(const char*);
			void setStatusTxt(const std::string&);
			void addStatusTxt(const char*);
			void addStatusTxt(const std::string&);
		protected:
			Gameboard& gameboard;
			Alien& alien;
			std::string commandTxt;
			std::string statusTxt;
			int statusCode;
			int turnCount;
		private:
			void requestInput();
			void processInput();
			
			void displayStoryCharacterStatus();
			void displayStatusTxt() const;
			void processCommandUp();
			void _processCommandUp();
			void processCommandDown();
			void processCommandLeft();
			void processCommandRight();
			void processCommandArrow();
			void processCommandHelp();
			void processCommandSave();
			void processCommandLoad();
	};
	
	
		
	class Health : public Object
	{
		public:
			Health();
			Health(const int point);
			//virtual ~Health();
			int getHealingPoint() const;
			virtual void encounterEvent(Alien& alien);
		private:
			int healingPoint;
	};
	
	
	class Arrow : public Object
	{
		public:
			Arrow();
			Arrow(const int attackPower, const char _symbol);
			Arrow(Arrow&);
			//virtual ~Arrow();
			int getAttackPower() const;
			virtual void encounterEvent(Alien& alien);
		private:
			int attackPower;
			
			
		
	};
	
	class Rock : public Object
	{
		public:
			Rock();
			//virtual ~Rock();
			virtual void encounterEvent(Alien& alien);
			virtual Object& reveal();
		protected:
			bool flipped;
			Object& discovered();
		
		private:
			
		
	};
	
	class Pod : public Object
	{
		public:
			Pod();
			//virtual ~Pod();
			virtual void encounterEvent(Alien& alien);
		
	};
	
	class Space : public Object
	{
		public:
			Space();
			//virtual ~Space();
			virtual void encounterEvent(Alien& alien);
	};
	
	class Trail : public Object
	{
		public:
			Trail();
			//virtual ~Trail();
			virtual void encounterEvent(Alien& alien);
			virtual Object& reveal();
	};
	
	
};

#endif
