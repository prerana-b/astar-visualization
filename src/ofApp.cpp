#include "ofApp.h"
#include "../Temporary.cpp"

pair<int, int> source(4, 4);
pair<int,int> final(0, 0);
astarClass obj(source, final);
int finished = -1;
int row = obj.getRow();
int col = obj.getCol();
bool showed = false;
std::stringstream stream;
vector<tuple<int, int>> finalPath;


//--------------------------------------------------------------
void ofApp::setup(){
	obj.changeState();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	
	if (finished != -1 && !showed) {
		finalPath = obj.generatePath();
		showed = true;
	}
		
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {

				if (i == source.first && j == source.second) {
					ofFill();
					ofSetColor(65, 105, 225, 255);
					ofDrawRectangle(i * 75 + 5, j * 75 + 5, 75, 75);
					ofSetColor(255, 255, 225, 255);
					ofDrawBitmapString("Start", i * 75 + 10, j * 75 + 80);

				}
				else if (i == final.first && j == final.second) {
					ofFill();
					ofSetColor(0, 100, 0, 255);
					ofDrawRectangle(i * 75 + 5, j * 75 + 5, 75, 75);
					ofSetColor(255, 255, 225, 255);
					ofDrawBitmapString("End", i * 75 + 10, j * 75 + 80);

				}
				else if (obj.grid[i][j] == 0) {
					ofFill();
					ofSetColor(165, 42, 42, 255);
					ofDrawRectangle(i * 75 + 5, j * 75 + 5, 75, 75);
				}
				else {
					if (obj.cellDetails[i][j].f > -1) {
						ofFill();
						ofSetColor(255, 20, 147, 255);
						ofDrawRectangle(i * 75 + 5, j * 75 + 5, 75, 75);
					}
					else {
						ofNoFill();
						ofSetColor(255, 255, 225, 255);
						ofDrawRectangle(i * 75 + 5, j * 75 + 5, 75, 75);
					}
				}

				if (!(i == source.first && j == source.second) && !(i == final.first && j == final.second)) {
					ofSetColor(255, 255, 225, 255);
					stream.str("");
					stream << std::fixed << std::setprecision(2) << obj.cellDetails[i][j].f;
					std::string s = stream.str();
					ofDrawBitmapString(s, i * 75 + 10, j * 75 + 80);
				}
			}
		}

		if (finished == 2) {
			for (tuple<int, int> o : finalPath) {
				if (!(get<0>(o) == source.first && get<1>(o) == source.second) && !(get<0>(o) == final.first && get<1>(o) == final.second)) {
					ofFill();
					ofSetColor(48, 25, 52, 255);
					ofDrawRectangle(get<0>(o) * 75 + 5, get<1>(o) * 75 + 5, 75, 75);

					ofSetColor(255, 255, 225, 255);
					stream.str("");
					stream << std::fixed << std::setprecision(2) << obj.cellDetails[get<0>(o)][get<1>(o)].f;
					std::string s = stream.str();
					ofDrawBitmapString(s, get<0>(o) * 75 + 10, get<1>(o) * 75 + 80);
				}
			}
			return;
		}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (finished == -1) {
		finished = obj.changeState();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}