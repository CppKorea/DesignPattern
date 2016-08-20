

#include "../model/NanaFrame.hpp"

namespace test
{
    using namespace sample;

    class SampleFrame : 
        public NanaFrame<NanaHPanel>
    {
    public:
        explicit SampleFrame():
            NanaFrame{}
        {
            using nana::colors;

            auto root_handle = root_panel->handle();

            // ���� : ���� �г�
            auto left = make_panel<NanaHPanel>(root_handle);
            {
                // R-G-B
                auto c1 = make_panel<NanaPanel>(left->handle());
                auto c2 = make_panel<NanaPanel>(left->handle());
                auto c3 = make_panel<NanaPanel>(left->handle());

                c1->background(colors::light_pink);
                c2->background(colors::light_green);
                c3->background(colors::light_blue);

                left->append(std::move(c1));
                left->append(std::move(c2));
                left->append(std::move(c3));
            }

            // ������ : ���� �г�
            auto right = make_panel<NanaVPanel>(root_handle);
            {
                // ��-��
                auto c1 = make_panel<NanaPanel>(right->handle());
                auto c2 = make_panel<NanaPanel>(right->handle());

                c1->background(colors::white);
                c2->background(colors::black);

                right->append(std::move(c1));
                right->append(std::move(c2));
            }

            // ��Ʈ �гο� ���
            root_panel->append(std::move(left));
            root_panel->append(std::move(right));
        }

    };

}// namespace test


int main(void)
{
    using namespace test;

    uptr<IFrame> frame = std::make_unique<SampleFrame>();
    frame->resize(640, 360);
    frame->show();

    // nana libray event loop
    // **blocks** until the form is closed.
    nana::exec();
}