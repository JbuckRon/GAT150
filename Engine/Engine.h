#pragma once
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"

#include "Audio/AudioSystem.h"

#include <memory>
#include <vector>

namespace neu
{
	extern AudioSystem g_audioSystem;
	extern Renderer g_renderer;
	extern InputSystem g_inputSystem;
	extern Time g_time;
}