#ifndef CONFIG_HPP_
#define CONFIG_HPP_



class Config {
   public:
   static Config& instance() {
        static Config instance;
        return instance;
    }
    // Constructeur par défaut
    void static reload();

   Config();
   Config(Config const&) = delete;

   private:


};

#endif  // CONFIG_HPP_