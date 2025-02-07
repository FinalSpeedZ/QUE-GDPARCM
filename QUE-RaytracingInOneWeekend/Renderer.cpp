#include "Renderer.h"

#include "DielectricMat.h"
#include "HittableList.h"
#include "LambertianMat.h"
#include "MetalMat.h"
#include "Sphere.h"
#include "Utils.h"
#include "WorkerRaytracer.h"

Renderer::Renderer()
{
    srand(static_cast<unsigned int>(time(0)));

    this->threadPool = NULL;

	this->camera = new Camera();

    camera->aspect_ratio = this->aspectRatio;
    camera->image_width = this->imgWidth;
    camera->samples_per_pixel = this->samplesPerPixel;
    camera->max_depth = this->rayMaxDepth;

    camera->vfov = 40;
    camera->lookfrom = Point3(-10, 4, -14);
    camera->lookat = Point3(-2, 1,-5);
    camera->vup = Vec3(0, 1, 0);

    camera->defocus_angle = 0.6;
    camera->focus_dist = (camera->lookfrom - camera->lookat).length(); // focus on the center

    this->camera->initialize();

    this->world = this->createWorld(300);
}

void Renderer::run()
{
    this->threadPool = new ThreadPool("TextureManagerPool", threadCount);
    this->threadPool->startScheduler();
    this->isRunning = true;

	this->image = new ImageSaver(this->imgWidth, this->imgHeight);

    std::string filename = "C:/Users/asus/Coding/GDPARCM/QUE-GDPARCM/QUE-RaytracingInOneWeekend/Png/Render.png";

    std::cout << "Image Res: " << this->imgWidth << ' ' << this->imgHeight << std::endl;
    std::cout << "Thread Count: " << threadCount << std::endl;

    for (int startRow = 0; startRow < imgHeight; startRow += rowsPerTask)
    {
        int endRow = std::min(startRow + rowsPerTask, imgHeight);

    	WorkerRaytracer* worker = new WorkerRaytracer(this->imgWidth, this->imgHeight, startRow, endRow,
            this->camera, this->world, image, this);

        this->threadPool->scheduleTask(worker);
    }

    while (this->isRunning)
    {
        if (this->linesRemaining == 0)
        {
            this->isRunning = false;
        }

        IETThread::sleep(1000);
    }

    this->image->saveImage(filename);
}

Hittable* Renderer::createWorld(int smallSpheres)
{
    HittableList* world = new HittableList();  

    auto ground_material = make_shared<LambertianMat>(Color(0.5, 0.5, 0.5));
    world->add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    int spheres = 0;

    while (spheres < smallSpheres)
    {
        for (int a = -20; a < 20; a++)
        {
            for (int b = -20; b < 20; b++)
            {
                auto choose_mat = random_double();
                Point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

                if ((center - Point3(4, 0.2, 0)).length() > 0.9)
                {
                    shared_ptr<Material> sphere_material;

                    if (choose_mat < 0.8)
                    {
                        auto albedo = Color::random() * Color::random();
                        sphere_material = make_shared<LambertianMat>(albedo);
                        world->add(make_shared<Sphere>(center, 0.2, sphere_material));
                    }
                    else if (choose_mat < 0.95)
                    {
                        auto albedo = Color::random(0.5, 1);
                        auto fuzz = random_double(0, 0.5);
                        sphere_material = make_shared<MetalMat>(albedo, fuzz);
                        world->add(make_shared<Sphere>(center, 0.2, sphere_material));
                    }
                    else
                    {
                        sphere_material = make_shared<DielectricMat>(1.5);
                        world->add(make_shared<Sphere>(center, 0.2, sphere_material));
                    }

                	spheres++;
                }
            }
        }
    }

    auto material1 = make_shared<DielectricMat>(1.5);
    world->add(make_shared<Sphere>(Point3(0, 1, -5), 1.0, material1));

    auto material2 = make_shared<LambertianMat>(Color(0.4, 0.2, 0.1));
    world->add(make_shared<Sphere>(Point3(-2.5, 1, -5), 1.0, material2));

    auto material3 = make_shared<MetalMat>(Color(0.7, 0.6, 0.5), 0.0);
    world->add(make_shared<Sphere>(Point3(2.5, 1, -5), 1.0, material3));

    auto material4 = make_shared<MetalMat>(Color(0.8, 0.2, 0.3), 0.0);
    world->add(make_shared<Sphere>(Point3(-5, 1, -5), 1.0, material4));

    return world;
}

void Renderer::onFinishedExecution()
{
    std::lock_guard<std::mutex> lock(guard);  
    this->linesRemaining -= rowsPerTask;

    if (this->linesRemaining <= 0)
    {
        this->isRunning = false;
    }

    std::cout << "Scanlines Remaining " << this->linesRemaining << std::endl;
}

