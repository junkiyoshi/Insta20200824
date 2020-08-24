#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofEnableDepthTest();

	this->cap.open("D:\\MP4\\openframeworks 2020-07-16 18-28-52.mp4");
	this->cap_size = cv::Size(720, 720);

	this->image.allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_COLOR);
	this->frame = cv::Mat(cv::Size(this->image.getWidth(), this->image.getHeight()), CV_MAKETYPE(CV_8UC3, this->image.getPixels().getNumChannels()), this->image.getPixels().getData(), 0);

	this->number_of_frames = this->cap.get(cv::CAP_PROP_FRAME_COUNT);
	for (int i = 0; i < this->number_of_frames; i++) {

		cv::Mat src, tmp;
		this->cap >> src;
		if (src.empty()) {

			continue;
		}

		cv::resize(src, tmp, this->cap_size);
		cv::cvtColor(tmp, tmp, cv::COLOR_BGR2RGB);

		this->frame_list.push_back(tmp);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	int n = ofGetFrameNum() % this->number_of_frames;
	this->frame_list[n].copyTo(this->frame);
	this->image.update();

	this->mesh.clear();

	int x_span = 144;
	int y_span = 72;

	vector<glm::vec3> base_location_list = { glm::vec3(-500, -500, 0), glm::vec3(-500, 500, 0), glm::vec3(500, -500, 0), glm::vec3(500, 500, 0) };

	for (auto& base_location : base_location_list) {
		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

		for (int i = 0; i < 5; i++) {

			int start_index = this->mesh.getNumVertices();

			// ã
			int x = this->cap_size.width * -0.5 + i * x_span * 0.5;
			int y = this->cap_size.height * -0.5 + i * y_span;
			int index = start_index;

			this->mesh.addVertex(glm::vec3(x, y, 0));
			this->mesh.addVertex(glm::vec3(x * -1, y, 0));
			this->mesh.addVertex(glm::vec3(x * -1, y + y_span, 0));
			this->mesh.addVertex(glm::vec3(x, y + y_span, 0));

			this->mesh.addTexCoord(glm::vec3(i * x_span * 0.5, i * y_span, 0));
			this->mesh.addTexCoord(glm::vec3(this->cap_size.width - i * x_span * 0.5, i * y_span, 0));
			this->mesh.addTexCoord(glm::vec3(this->cap_size.width - i * x_span * 0.5, i * y_span + y_span, 0));
			this->mesh.addTexCoord(glm::vec3(i * x_span * 0.5, i * y_span + y_span, 0));

			this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 1); this->mesh.addIndex(index + 2);
			this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 2); this->mesh.addIndex(index + 3);

			// ¶
			index = this->mesh.getNumVertices();

			this->mesh.addVertex(glm::vec3(x, y + y_span, 0));
			this->mesh.addVertex(glm::vec3(x + x_span * 0.5, y + y_span, 0));
			this->mesh.addVertex(glm::vec3(x + x_span * 0.5, y * -1 - y_span, 0));
			this->mesh.addVertex(glm::vec3(x, y * -1 - y_span, 0));

			this->mesh.addTexCoord(glm::vec3(i * x_span * 0.5, i * y_span + y_span, 0));
			this->mesh.addTexCoord(glm::vec3(i * x_span * 0.5 + x_span * 0.5, i * y_span + y_span, 0));
			this->mesh.addTexCoord(glm::vec3(i * x_span * 0.5 + x_span * 0.5, this->cap_size.height - i * y_span - y_span, 0));
			this->mesh.addTexCoord(glm::vec3(i * x_span * 0.5, this->cap_size.height - i * y_span - y_span, 0));

			this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 1); this->mesh.addIndex(index + 2);
			this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 2); this->mesh.addIndex(index + 3);

			// ‰º

			y = this->cap_size.height * 0.5 - i * y_span - y_span;
			index = this->mesh.getNumVertices();

			this->mesh.addVertex(glm::vec3(x, y, 0));
			this->mesh.addVertex(glm::vec3(x * -1, y, 0));
			this->mesh.addVertex(glm::vec3(x * -1, y + y_span, 0));
			this->mesh.addVertex(glm::vec3(x, y + y_span, 0));

			this->mesh.addTexCoord(glm::vec3(i * x_span * 0.5, this->cap_size.height - i * y_span - y_span, 0));
			this->mesh.addTexCoord(glm::vec3(this->cap_size.width - i * x_span * 0.5, this->cap_size.height - i * y_span - y_span, 0));
			this->mesh.addTexCoord(glm::vec3(this->cap_size.width - i * x_span * 0.5, this->cap_size.height - i * y_span, 0));
			this->mesh.addTexCoord(glm::vec3(i * x_span * 0.5, this->cap_size.height - i * y_span, 0));

			this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 1); this->mesh.addIndex(index + 2);
			this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 2); this->mesh.addIndex(index + 3);

			// ‰E

			x = this->cap_size.width * 0.5 - i * x_span * 0.5 - x_span * 0.5;
			y = this->cap_size.height * -0.5 + i * y_span;
			index = this->mesh.getNumVertices();

			this->mesh.addVertex(glm::vec3(x, y + y_span, 0));
			this->mesh.addVertex(glm::vec3(x + x_span * 0.5, y + y_span, 0));
			this->mesh.addVertex(glm::vec3(x + x_span * 0.5, y * -1 - y_span, 0));
			this->mesh.addVertex(glm::vec3(x, y * -1 - y_span, 0));

			this->mesh.addTexCoord(glm::vec3(this->cap_size.width - i * x_span * 0.5 - x_span * 0.5, i * y_span + y_span, 0));
			this->mesh.addTexCoord(glm::vec3(this->cap_size.width - i * x_span * 0.5, i * y_span + y_span, 0));
			this->mesh.addTexCoord(glm::vec3(this->cap_size.width - i * x_span * 0.5, this->cap_size.height - i * y_span - y_span, 0));
			this->mesh.addTexCoord(glm::vec3(this->cap_size.width - i * x_span * 0.5 - x_span * 0.5, this->cap_size.height - i * y_span - y_span, 0));

			this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 1); this->mesh.addIndex(index + 2);
			this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 2); this->mesh.addIndex(index + 3);

			for (int k = start_index; k < this->mesh.getNumVertices(); k++) {

				auto angle_x = ofMap(ofNoise(noise_seed.x, i * 0.085 + ofGetFrameNum() * 0.005), 0, 1, -PI, PI);
				auto angle_y = ofMap(ofNoise(noise_seed.y, i * 0.085 + ofGetFrameNum() * 0.005), 0, 1, -PI, PI);
				auto angle_z = ofMap(ofNoise(noise_seed.z, i * 0.085 + ofGetFrameNum() * 0.005), 0, 1, -PI, PI);

				auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

				glm::vec3 vertex = glm::vec4(this->mesh.getVertex(k), 0) * rotation_y * rotation_x;
				vertex += base_location;

				this->mesh.setVertex(k, vertex);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	ofSetColor(255);
	this->image.bind();
	this->mesh.draw();
	this->image.unbind();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}