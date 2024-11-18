#include "06.01_class.hpp"

namespace stdhate {
Entity::Entity() : m_data_1(s_data_1), m_data_2(0), m_data_3(0) {}

Entity::Entity(const int& data_1, int data_2, int data_3)
    : m_data_1(data_1), m_data_2(data_2), m_data_3(data_3) {}

Entity::Entity(const int& data_1, int data_2) : Entity(data_1, data_2, 0) {}

Entity::~Entity() { std::clog << "Entity::~Entity\n"; }

int Entity::data_1() const { return m_data_1; }

int Entity::data_2() const { return m_data_2; }

int Entity::data_3() const { return m_data_3; }

const std::string& Entity::data_as_string() const {
  //	m_data_3 = 0; // error

  if (m_cached_data.is_invalid) {
    m_cached_data.update(*this);
  }

  return m_cached_data.string;
}

void Entity::set_data_3(int data) {
  m_data_3 = data;

  m_cached_data.is_invalid = true;
}

void Entity::test() {
  std::clog << "Entity::test : s_data_1 = " << s_data_1 << '\n';

  //		std::clog << "Entity::test : m_data_3 = " << m_data_3 << '\n';
  //// error
}

void Entity::Cached_Data::update(const Entity& entity) {
  string =
      (std::to_string(entity.m_data_1) + '/' + std::to_string(entity.m_data_2) +
       '/' + std::to_string(entity.m_data_3));

  is_invalid = false;
}
}  // namespace stdhate