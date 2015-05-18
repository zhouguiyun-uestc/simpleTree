#include "workerspherefollowing.h"

WorkerSphereFollowing::WorkerSphereFollowing(QObject *parent)
{
}

void
WorkerSphereFollowing::run()
{


    SphereFollowing sphereFollowing ( this->control->getCloudPtr (), control, 1, coefficients );
    boost::shared_ptr<simpleTree::Tree> tree = boost::make_shared<simpleTree::Tree> ( sphereFollowing.getCylinders (), control->getCloudPtr (),
                                                                                     control->getTreeID (), this->control ,false);

    simpleTree::Allometry allom;
    allom.setTree(tree);
    allom.setCoefficients(2101,3.775);
    allom.setFac(1.6);
    allom.improveTree();
    //control ->setTreePtr ( tree );


    std::vector<float> distances = tree->distancesToModel ();
    meanDist = control->getGuiPtr()->average(distances);

    std::cout << "in worker distance " << meanDist << std::endl;


    if(optimize->get_current_dist()>meanDist)
    {
        optimize->updateCoeff(this->coefficients, meanDist);
        //control->setTreePtr(tree);
    }



}


void
WorkerSphereFollowing::setOptimize(boost::shared_ptr<Optimization> optimize)
{
    this->optimize = optimize;
}

void
WorkerSphereFollowing::set_control(boost::shared_ptr<Controller> control)
{
    this->control = control;
}

void
WorkerSphereFollowing::set_coefficients(Method_Coefficients coefficients)
{
    this->coefficients = coefficients;
}
