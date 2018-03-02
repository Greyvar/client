#!groovy

properties (
    [
         buildDiscarder(logRotator(artifactDaysToKeepStr: '', artifactNumToKeepStr: '', daysToKeepStr: '', numToKeepStr: '10')),
         [$class: 'CopyArtifactPermissionProperty', projectNames: '*'],
         pipelineTriggers([[$class: 'PeriodicFolderTrigger', interval: '1d']])
    ]
)

def prepareEnv() {
    deleteDir()
    unstash "binaries"

    env.WORKSPACE = pwd()

    sh "find ${env.WORKSPACE}"

    sh "mkdir -p SPECS SOURCES"
    sh "cp build/distributions/*.zip SOURCES/upsilon-custodian.zip"
}


def buildRpm(dist) {
    prepareEnv()

    sh 'unzip -jo SOURCES/upsilon-custodian.zip "upsilon-custodian-*/var/pkg/upsilon-custodian.spec" "upsilon-custodian-*/.buildid.rpmmacro" -d SPECS/'
    sh "find ${env.WORKSPACE}"

    sh "rpmbuild -ba SPECS/upsilon-custodian.spec --define '_topdir ${env.WORKSPACE}' --define 'dist ${dist}'"

    archive 'RPMS/noarch/*.rpm'
    stash "${dist}"
}


node {
	stage("Prep") {
		checkout scm
		sh "buildid -n"
	}

	stage("Build-lin") {
		sh "rm -rf build CMakeFiles CMakeCache.txt "
		sh 'cmake .'
		sh 'make'

	}

	stage("Build-win") {
		sh "rm -rf build CMakeFiles CMakeCache.txt "
		sh 'cmake -DCMAKE_TOOLCHAIN_FILE=../windows.cmake .'
		sh 'make'
	}

	stage("Package") {
		sh "ant package"

		archive 'pkg/**'

		stash includes: 'pkg/**', name: 'binaries'
	}
}
