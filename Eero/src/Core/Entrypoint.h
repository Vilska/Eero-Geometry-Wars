#pragma once

extern std::shared_ptr<Eero::Application> Eero::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Eero::CreateApplication();
	app->Run();
}
