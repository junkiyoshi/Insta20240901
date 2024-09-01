#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	auto p = ofGetFrameNum() % 50;

	if (p < 12) {

		this->noise_param += ofMap(p, 0, 12, 0.25, 0.0);
	}
	else if(p > 88){

		this->noise_param += ofMap(p, 88, 100, 0, 0.25);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofMesh mesh;

	float span = 0.5;
	float noise_param = ofRandom(1000);
	for (int i = 0; i < 8; i++) {

		noise_param += 0.06;
		for (float x = 50; x <= 670; x += span) {

			for (float y = 50; y <= 670; y += span) {

				float noise_value = ofNoise(noise_param, x * 0.005, y * 0.005, this->noise_param);
				if ((noise_value >= 0.42 && noise_value <= 0.48)) {

					mesh.addVertex(glm::vec3(x, y, 0));
					mesh.addVertex(glm::vec3(x + span, y, 0));
					mesh.addVertex(glm::vec3(x + span, y + span, 0));
					mesh.addVertex(glm::vec3(x, y + span, 0));

					mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 4); mesh.addIndex(mesh.getNumVertices() - 3);
					mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 2); mesh.addIndex(mesh.getNumVertices() - 3);

					for (int i = 0; i < 4; i++) {

						mesh.addColor(ofColor(12));
					}
				}
			}
		}

		mesh.draw();
	}

	/*
	int start = 1;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}