#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/placeholder_texture2d.hpp>
#include <godot_cpp/classes/video_stream.hpp>
#include <godot_cpp/classes/video_stream_playback.hpp>

using namespace godot;

// VideoStreamDynamic

class VideoStreamDynamic : public VideoStream {
	GDCLASS(VideoStreamDynamic, VideoStream)

public:
	Ref<VideoStreamPlayback> _instantiate_playback() override;

protected:
	static void _bind_methods();
};

// VideoStreamPlaybackDynamic

class VideoStreamPlaybackDynamic : public VideoStreamPlayback {
	GDCLASS(VideoStreamPlaybackDynamic, VideoStreamPlayback)

public:
	VideoStreamPlaybackDynamic();
	~VideoStreamPlaybackDynamic();
	void _play() override;
	void _stop() override;
	bool _is_playing() const override;
	void _set_paused(bool p_paused) override;
	bool _is_paused() const override;
	double _get_length() const override;
	double _get_playback_position() const override;
	void _seek(double p_time) override;
	void _set_audio_track(int32_t p_idx) override;
	int32_t _get_channels() const override;
	int32_t _get_mix_rate() const override;
	Ref<Texture2D> _get_texture() const override;
	void _update(double p_delta) override;

protected:
	static void _bind_methods();

private:
	bool playing = false;
	bool paused = false;
	Ref<PlaceholderTexture2D> texture;
	double time = 0;
};

// VideoStreamDynamic

Ref<VideoStreamPlayback> VideoStreamDynamic::_instantiate_playback() {
	Ref<VideoStreamPlaybackDynamic> pb = memnew(VideoStreamPlaybackDynamic);
	return pb;
}

void VideoStreamDynamic::_bind_methods() {
}

// VideoStreamPlaybackDynamic

VideoStreamPlaybackDynamic::VideoStreamPlaybackDynamic() {
	texture.instantiate();
}

VideoStreamPlaybackDynamic::~VideoStreamPlaybackDynamic() {
	texture.unref();
}

void VideoStreamPlaybackDynamic::_play() {
	playing = true;
}

void VideoStreamPlaybackDynamic::_stop() {
	playing = false;
}

bool VideoStreamPlaybackDynamic::_is_playing() const {
	return playing;
}

void VideoStreamPlaybackDynamic::_set_paused(bool p_paused) {
	paused = p_paused;
}

bool VideoStreamPlaybackDynamic::_is_paused() const {
	return paused;
}

double VideoStreamPlaybackDynamic::_get_length() const {
	return 0.0;
}

double VideoStreamPlaybackDynamic::_get_playback_position() const {
	return 0.0;
}

void VideoStreamPlaybackDynamic::_seek(double p_time) {
}

void VideoStreamPlaybackDynamic::_set_audio_track(int32_t p_idx) {
}

int32_t VideoStreamPlaybackDynamic::_get_channels() const {
	return 0;
}

int32_t VideoStreamPlaybackDynamic::_get_mix_rate() const {
	return 48000;
}

Ref<Texture2D> VideoStreamPlaybackDynamic::_get_texture() const {
	return texture;
}

void VideoStreamPlaybackDynamic::_update(double p_delta) {
	time += p_delta;
	texture->set_size(Vector2(((int32_t)time % 6) * 100, 500));
}

void VideoStreamPlaybackDynamic::_bind_methods() {
}

// GDExtension

void initialize(ModuleInitializationLevel p_level) {
	switch (p_level) {
		case MODULE_INITIALIZATION_LEVEL_SCENE: {
			GDREGISTER_CLASS(VideoStreamDynamic);
			GDREGISTER_CLASS(VideoStreamPlaybackDynamic);
		} break;
	}
}

void uninitialize(ModuleInitializationLevel p_level) {
	switch (p_level) {
		case MODULE_INITIALIZATION_LEVEL_SCENE: {
		} break;
	}
}

extern "C" {
// Initialization
GDExtensionBool GDE_EXPORT dynamic_video_stream_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize);
	init_obj.register_terminator(uninitialize);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
	return init_obj.init();
}
}
