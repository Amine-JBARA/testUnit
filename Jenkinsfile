pipeline {
  agent any

  stages {
    stage('Checkout') {
      steps {
              echo 'Pulling...';
              git branch: 'main',
              url : 'https://github.com/Amine-JBARA/testUnit.git';
      }
    }
        stage('Run test daemon') {
      steps {
    sh 'g++ ./files/daemon.cpp ./gtest-daemon/daemonTest.cpp -lsqlite3 -lgtest -lgtest_main -pthread -o main.exe'
    sh './main.exe'
      }
    }

    // Add more stages and steps as needed
  }
}