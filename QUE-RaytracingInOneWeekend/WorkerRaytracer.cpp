#include "WorkerRaytracer.h"

#include "Color.h"
#include "Ray.h"
#include "Camera.h"
#include "IExecutionEvent.h"

WorkerRaytracer::WorkerRaytracer(int imgWidth, int imgHeight, int startRow, int endRow,
    Camera* camera, Hittable* world, ImageSaver* imageSaver, IExecutionEvent* executionEvent)

    : imgWidth(imgWidth), imgHeight(imgHeight), startRow(startRow), endRow(endRow),
      camera(camera), world(world), imageSaver(imageSaver), executionEvent(executionEvent)
{
    this->samplesPerPixel = this->camera->samples_per_pixel;
    this->maxDepth = this->camera->max_depth;
}

void WorkerRaytracer::onStartTask()
{

    for (int row = startRow; row < endRow; row++)
    {
        for (int i = 0; i < imgWidth; i++)
        {
            Color pixel_color(0, 0, 0);

            for (int sample = 0; sample < this->samplesPerPixel; sample++)
            {
                Ray r = camera->get_ray(i, row);
                pixel_color += camera->ray_color(r, this->maxDepth, *world);
            }

            Vec3 color = write_color((1.0 / this->samplesPerPixel) * pixel_color);

            this->imageSaver->setPixel(i, row, int(color.x()), int(color.y()), int(color.z()), this->samplesPerPixel);
        }

    }

    this->executionEvent->onFinishedExecution();
    delete this;
}


