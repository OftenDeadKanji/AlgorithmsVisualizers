
class View;
class Model;

class Controller
{
public:
	Controller(Model& model, View& view);

	bool shouldApplicationRun() const;
private:
	Model& m_model;
	View& m_view;

	bool m_shouldApplicationRun = true;
};