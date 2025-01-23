class Application {
    protected:
        int width, height;

    public:
        virtual const char* getTitle(); 
        virtual void initGraphics();
        virtual void setView(); 
        virtual void deinit();
        virtual void display();
        virtual void update();
        virtual void key(unsigned char key);
        virtual void mouse(int button, int state, int x, int y);
};