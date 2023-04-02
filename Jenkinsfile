/* Requires the Docker Pipeline plugin */
pipeline {
    agent { docker { image 'gcc:latest' } }
    stages {
        stage('build') {
            steps {
                sh 'gcc --version'
            }
        }
    }
}
