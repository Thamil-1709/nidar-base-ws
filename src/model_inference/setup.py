from setuptools import find_packages, setup

package_name = 'model_inference'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
         ('share/' + package_name + '/models', ['models/best.pt']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='thamil-selva',
    maintainer_email='tamilselvan1709@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
         "model_inference_node = model_inference.model_inference_node:main",
            "img2gps_node = model_inference.img2gps_node:main",
        ],
    },
)
